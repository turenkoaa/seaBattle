#include "myserver.h"

int toInt(QString str)
{
    if (str == "ready") return 1;
    if (str == "new game") return 2;
    if (str == "end game") return 3;
    else return 0;
}

MyServer::MyServer(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt)
                                                    , m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);

    if (!m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        QMessageBox::critical(0,"Server Error","Unable to start the server:" + m_ptcpServer->errorString());
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()),this,SLOT(slotNewConnection()));

    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true);

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}

int MyServer::findEnemy(int id)
{
    QHash<int, Client*>::iterator it = clients.begin();
    for (; it != clients.end() ; it++)
    {
        if (it.key() != id)
        if (it.value()->hasEnemy == false)
        {
            it.value()->hasEnemy = true;
            it.value()->enemyId = id;

            //отправить противнику, что он готов к игре
           sendToClient(it.value()->getClientSocket(), "find", -1, -1);
           qDebug() << it.key() << " vs " << id;

           QString str1, str2;
           str1.setNum(it.key());
           str2.setNum(id);
           m_ptxt->append(str1 + " vs " + str2);


           return it.key();
        }
    }
    return -1;
}

void MyServer::newEnemy(int idUser)
{
    clients[idUser]->enemyId = findEnemy(idUser);
    if (clients[idUser]->enemyId != -1)
    {
        clients[idUser]->hasEnemy = true;
        sendToClient(clients[idUser]->getClientSocket(), "find", -1, -1);
        qDebug() << idUser << " vs " << clients[idUser]->enemyId;
    }
}

/*virtual*/ void MyServer::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();

    //получаем дескриптор нового сокета
    int idUser = pClientSocket->socketDescriptor();

    //добавляем нового клиента
    clients.insert(idUser, new Client(pClientSocket, idUser));
    qDebug() << "Новый клиент:" <<  idUser;

    QString str;
    str.setNum(idUser);
    m_ptxt->append("Новый клиент: " + str);


    //ищем ему противника
    newEnemy(idUser);
    connect(clients[idUser]->getClientSocket(), SIGNAL(disconnected()), clients[idUser], SLOT(disconnected()));
    connect(clients[idUser], SIGNAL(deleteClient(int)), this, SLOT(slotDeleteUser(int)));
    connect(clients[idUser]->getClientSocket(), SIGNAL(readyRead()), this,SLOT(slotReadClient()));

}

void MyServer::slotDeleteUser(int id)
{
     qDebug() << id << "вышел";

     QString str;
     str.setNum(id);
     m_ptxt->append(str + " вышел");


     //clients[id]->getClientSocket()->close();
     if (clients[id]->hasEnemy == true)
     {
         int enemyId = clients[id]->enemyId;
         clients[enemyId]->hasEnemy = false;
         sendToClient(clients[enemyId]->getClientSocket(), "enemy left", -1, -1);
         newEnemy(enemyId);
     }
    clients.remove(id);

    m_ptxt->append("");
    m_ptxt->append("Клиенты:");
    qDebug() << "Клиенты: ";
    QHash<int, Client*>::iterator it = clients.begin();
    for (; it != clients.end(); it++)
    {
        qDebug() << it.key();
        QString str;
        str.setNum(it.key());
        m_ptxt->append(str);

    }
    m_ptxt->append("");
}

void MyServer::pricessRequest(int idUser, QString str, int coordI, int coordJ)
{
   /*if (coordI == -10)
   {
       clients[idUser]->name = str;

       QHash<int, Client*>::iterator it = clients.begin();
       for (; it != clients.end() ; it++)
           if (it.key() != idUser)
               sendToClient(clients[clients[id.key()]->enemyId]->getClientSocket(), str ,-10, -10);

       qDebug() << idUser << " - " << str;
   }
   else*/
   switch (toInt(str))
   {
   case 1: //ready
   {
       clients[idUser]->ready = true;

       qDebug() << idUser << "is ready";

       QString str;
       str.setNum(idUser);
       m_ptxt->append(str + " готов к игре");


       if (clients[clients[idUser]->enemyId]->ready == true) sendToClient(clients[clients[idUser]->enemyId]->getClientSocket(), "go", -1, -1);
       break;
   }
   case 2:
   {

       QString str;
       str.setNum(idUser);
       m_ptxt->append(str + " хочет начать новую игру");


       int enemyId = clients[idUser]->enemyId;
       if (clients[idUser]->hasEnemy == true)
       {
           enemyId = clients[idUser]->enemyId;
       }
       else enemyId = -1;

       clients[idUser]->hasEnemy = false;
       newEnemy(idUser);

       if (enemyId != -1)
       {
           clients[enemyId]->hasEnemy = false;
           sendToClient(clients[enemyId]->getClientSocket(), "enemy left", -1, -1);
           newEnemy(enemyId);
       }

       break;
   }
   case 3:
   {
       QString str;
       str.setNum(idUser);
       m_ptxt->append(str + " хочет начать новую игру");


       clients[idUser]->hasEnemy = false;
       newEnemy(idUser);
       break;
   }
   default:

       QString id, str1, str2;
       id.setNum(idUser);
       str1.setNum(coordI);
       str2.setNum(coordJ);
       m_ptxt->append(id + " отравил:");
       m_ptxt->append(str + ": " + str1 + ", " + str2);


       sendToClient(clients[clients[idUser]->enemyId]->getClientSocket(), str, coordI, coordJ);
        break;
   }
}

void MyServer::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QString str;

        int i;
        int j;
        in >> str >> i >> j;

        int idUserSocs = pClientSocket->socketDescriptor();
        qDebug() << "Пишет: " << idUserSocs;
        qDebug() << str << i << j;


        m_nNextBlockSize = 0;

        //обработка запроса
        pricessRequest(idUserSocs, str, i, j);

    }
}

void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str, int i, int j)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);
    out << quint16(0) << str << i << j;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);

}

