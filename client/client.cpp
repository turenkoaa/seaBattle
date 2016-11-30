#include "client.h"
#include "ui_client.h"

int toInt(QString str)
{
    if (str == "go") return 1;
    if (str == "step") return 2;
    if (str == "boner") return 3;
    if (str == "kill") return 5;
    if (str == "hit") return 4;
    if (str == "end") return 6;
    if (str == "find") return 7;
    if (str == "bonerPic") return 8;
    if (str == "enemy left") return 9;
    else return 0;
}

Client::Client(const QString& strHost, int nPort, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client),
    m_nNextBlockSize(0),
    state(Placing_Ships),
        size(30, 30),
        name("")
{
    ui->setupUi(this);

       m_pTcpSocket = new QTcpSocket(this);

       m_pTcpSocket->connectToHost(strHost, nPort);

       connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
       connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
       connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

       QPushButton* pcmd = new QPushButton("&Send");
       connect(pcmd, SIGNAL(clicked()), this, SLOT(slotSendToServer()));

       const int m = 10;

       QVBoxLayout* mainLayout = new QVBoxLayout();
       QHBoxLayout* widgetLayout = new QHBoxLayout();
       QGridLayout* yourButtonsLayout = new QGridLayout();
       QGridLayout* enemyButtonsLayout = new QGridLayout();
       yourButtons= new QPushButton**[m];
       enemyButtons= new QPushButton**[m];

       points= new Point**[m];

       //связь с кнопками поля игрока
       for(int i = 0; i < m; ++i)
       {
           yourButtons[i] = new QPushButton*[m];
           points[i]=new Point*[m];

           for(int j = 0; j < m; ++j)
           {
               points[i][j]=new Point(i,j);
               yourButtons[i][j]=new QPushButton();
               yourButtons[i][j]->setIcon(QIcon());
               yourButtons[i][j]->setIconSize(size);
               yourButtons[i][j]->setFixedSize(size);


               QPalette pal = yourButtons[i][j]->palette();
               pal.setColor(QPalette::Button, color);
               yourButtons[i][j]->setAutoFillBackground(true);
               yourButtons[i][j]->setPalette(pal);
               yourButtons[i][j]->update();
               //yourButtons[i][j]->setFlat(true);

               yourButtonsLayout->setSpacing(0);
               yourButtonsLayout->addWidget(yourButtons[i][j],i,j);
               QObject::connect(yourButtons[i][j],SIGNAL(clicked()),points[i][j],SLOT(toResiveASignal()));
           }
       }

       //связь с кнопками поля врага
       for(int i = 0; i < m; ++i)
       {
           enemyButtons[i] = new QPushButton*[m];
           for(int j = 0; j < m; ++j)
           {
               enemyButtons[i][j]=new QPushButton();
               enemyButtons[i][j]->setIcon(QIcon());
               enemyButtons[i][j]->setIconSize(size);
               enemyButtons[i][j]->setFixedSize(size);

               QPalette pal = enemyButtons[i][j]->palette();
               pal.setColor(QPalette::Button, color);
               //pal.setColor(QPalette::Button, QColor(89, 65, 17, 150));
               enemyButtons[i][j]->setAutoFillBackground(true);
               enemyButtons[i][j]->setPalette(pal);
               enemyButtons[i][j]->update();

               enemyButtonsLayout->setSpacing(0);
               enemyButtonsLayout->addWidget(enemyButtons[i][j],i,j);
               QObject::connect(enemyButtons[i][j],SIGNAL(clicked()),points[i][j],SLOT(toResiveASignal()));
           }
       }

       //соединение пойнтов со слотом виджета
       for(int i = 0; i < m; ++i)
           for(int j = 0; j < m; ++j)
           {
               QObject::connect(points[i][j],SIGNAL(reciveCoordinates(int, int)),this,SLOT(buttonPressed(int, int)));
           }

       widgetLayout->addLayout(yourButtonsLayout);
       widgetLayout->addSpacing(30);
       widgetLayout->setMargin(20);
       widgetLayout->addLayout(enemyButtonsLayout);
       mainLayout->addLayout(widgetLayout);
       this->setLayout(mainLayout);

       boardPlayer = new Player();
       boardBot=new Player();

       //задание флота противника
       //boardBot->SetShips();

       ui->infoLabel->setText("Let`s build your flot! Choose one-desk ship.");

       //неверный корабль
       connect(this->boardPlayer,SIGNAL(needClear()),this,SLOT(clearShip()));
       //сделать кнопки недоступными
       connect(this->boardPlayer,SIGNAL(needBlock()),this,SLOT(blockShip()));
       //одно поле доступно, другое нет
       connect(this->boardPlayer, SIGNAL(needBlockField1()), this, SLOT(blockField1()));
       connect(this->boardBot, SIGNAL(needBlockField2()), this, SLOT(blockField2()));
       //конец расставления кораблей
       connect(this->boardPlayer,SIGNAL(endPlace()),this,SLOT(endPlaceSlot()));
       //завершение игры
       connect(this->boardPlayer,SIGNAL(endGame()),this,SLOT(endGame()));
       //удар мимо
       connect(this->boardPlayer,SIGNAL(signBonerPic(int, int)),this,SLOT(setBoner(int, int)));
       connect(this->boardPlayer,SIGNAL(signBoner(int, int)),this,SLOT(youBoner(int, int)));
       //удар попал
       connect(this->boardPlayer,SIGNAL(signHit(int, int)),this,SLOT(youHit(int, int)));
       //удар убил
       connect(this->boardPlayer,SIGNAL(signKill(int, int)),this,SLOT(youKill(int, int)));
       //меняем информационную строку
       connect(this->boardPlayer,SIGNAL(oneDeskShip()),this,SLOT(labelOneDesk()));
       connect(this->boardPlayer,SIGNAL(twoDeskShip()),this,SLOT(labelTwoDesk()));
       connect(this->boardPlayer,SIGNAL(threeDeskShip()),this,SLOT(labelThreeDesk()));
       connect(this->boardPlayer,SIGNAL(fourDeskShip()),this,SLOT(labelFourDesk()));
       //меняем стиль
       connect(this, SIGNAL(styleSea()), this, SLOT(setStyle()));

       connect(ui->autoBuild, SIGNAL(clicked()), SLOT(autoBuildFlot()));
       connect(boardPlayer, SIGNAL(signShip(int,int)), SLOT(slotSetShip(int, int)));

       //QObject::connect(this->boardPlayer,SIGNAL(endGame(Player*)),this,SLOT(endGame(Player*)));
       //ход противника
       //QObject::connect(this,SIGNAL(waitingStep()),this,SLOT(enemyAttack()));
       //QObject::connect(this->boardBot,SIGNAL(nextTurn()),this,SLOT(enemyAttack()));
       //QObject::connect(this->boardBot,SIGNAL(signBoner(int, int)),this,SLOT(enemyBoner(int, int)));
       //QObject::connect(this->boardBot,SIGNAL(signHit(int, int)),this,SLOT(enemyHit(int, int)));
       //QObject::connect(this->boardBot,SIGNAL(signKill(int, int)),this,SLOT(enemyKill(int, int)));


       blockEnemyField();
}

Client::~Client()
{
    delete ui;
    delete yourButtons;
    delete enemyButtons;
    delete boardPlayer;
    delete boardBot;
    delete kill;
    delete past;
    delete button;
    delete shipHit;

}

void Client::slotNewGame()
{
    SendToServer("new game", -1, -1);
    playAgain();
}

void Client::slotEndGame()
{
    SendToServer("end game", -1, -1);
    playAgain();
}

void Client::checkAnswer(QString str, int i, int j)
{

    /*if (i == -10)
    {
        emit signAddPlayer(str);
    } else*/
    switch(toInt(str))
    {
    case 1: //go
    {
        blockYourField();
        ui->infoLabel->setText("Make step, good luck!");
        break;
    }
    case 2: //step
    {
        Cell cell(i+1, j+1);
        boardPlayer->checkAttack(cell);
        break;
    }
    case 3: //boner
    {
        enemyButtons[i-1][j-1]->setIcon(*past);
        blockBothFields();
        SendToServer("go", -1, -1);
        ui->infoLabel->setText("Wait for your enemy step!");
        break;
    }
    case 4: //hit
    {
        int ii=i-1;
        int jj=j-1;
        enemyButtons[ii][jj]->setIcon(*shipHit);
        enemyButtons[ii][jj]->setIconSize(size);
        //enemyButtons[ii][jj]->setEnabled(false);
        if (i-1!=0 && i-1!=11 && j-1!=0 && j-1!=11)
        {
            enemyButtons[ii-1][jj-1]->setIcon(*past);
            //enemyButtons[ii-1][jj-1]->setEnabled(false);
        }
        if (i-1!=0 && i-1!=11 && j+1!=0 && j+1!=11)
        {
            enemyButtons[ii-1][jj+1]->setIcon(*past);
            //enemyButtons[ii-1][jj+1]->setEnabled(false);
        }
        if (i+1!=0 && i+1!=11 && j-1!=0 && j-1!=11)
        {
            enemyButtons[ii+1][jj-1]->setIcon(*past);
           // enemyButtons[ii+1][jj-1]->setEnabled(false);
        }
        if (i+1!=0 && i+1!=11 && j+1!=0 && j+1!=11)
        {
            enemyButtons[ii+1][jj+1]->setIcon(*past);
           // enemyButtons[ii+1][jj+1]->setEnabled(false);
        }

        break;
    }
    case 5: //kill
    {
        enemyButtons[i-1][j-1]->setIcon(*kill);
        enemyButtons[i-1][j-1]->setIconSize(size);
        break;
    }
    case 6: //end
    {
        blockBothFields();
        ui->infoLabel->setText("You won. Congratulatons!");
        emit endGameWin(true);
        break;
    }
    case 7: //find
    {
        emit signalFindEnemy();
        qDebug() << "find";
        break;
    }
    case 8: //bonerPic
    {
        enemyButtons[i-1][j-1]->setIcon(*past);
        break;
    }
    case 9:
    {
       qDebug() << "противник вышел";
       playAgain();
       emit needNewEnemy(1);
       break;
    }

    }
}

void Client::slotSendName(QString name)
{
    this->name = name;
    SendToServer(name, -10, -10);
}

void Client::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;)
    {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16))
                break;
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) break;

        //QTime time;
        QString str;
        int i;
        int j;

        in >> str >> i >> j;

        qDebug() << "Получил: " << str << i << j;
        checkAnswer(str, i, j);

        m_nNextBlockSize = 0;



    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                             "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                              "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                              "The connection was refused." :
                         QString(m_pTcpSocket->errorString()));

    emit signalDisconnected();
}

void Client::SendToServer(QString str,int i, int j)
{

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly); //создаем поток в который записываем все данные блока
    out.setVersion(QDataStream::Qt_4_5);

    qDebug() << "Запроc: " << str << i << j;
    out << quint16(0) << str << i << j;

    out.device()->seek(0);                             //перемещаем указатель на начало блока
    out << quint16(arrBlock.size() - sizeof(quint16)); //вычисляем размер блока как размер arrBlock, уменьшенный на quint16
                                                       //записываем его в поток
    m_pTcpSocket->write(arrBlock);

}
void Client::slotConnected()
{
    emit signalConnected();
}

Point::Point(int fori, int forj){
    this->i=fori;
    this->j=forj;
}
void Point::toResiveASignal()
{
    emit reciveCoordinates(this->i,this->j);
}

/*
 *
void Widget::setEasyLevel()
{
    level=easy;
}
void Widget::setVeryEasyLevel()
{
    level=very_easy;
}
void Widget::setMediumLevel()
{
    level=medium;
}
void Widget::setHardLevel()
{
    level=hard;
}
void Widget::setVeryHardLevel()
{
    level=very_hard;
}
*/

void Client::buttonPressed(int i, int j){

    Cell cell(i+1, j+1);

      switch (state)
        {
        case Placing_Ships:
        {
          ui->autoBuild->setEnabled(false);
          yourButtons[i][j]->setIcon(*button);
          yourButtons[i][j]->setIconSize(size);
          boardPlayer->GetShips(cell);
          break;

        }
        case Making_Step:
        {
            SendToServer("step", i, j);
            qDebug() << i << j;
           //boardBot->checkAttack(cell);
           //emit waitingStep();
           break;
        }
    }
}

void Client::slotSetShip(int i, int j)
{
    yourButtons[i][j]->setIcon(*button);
    yourButtons[i][j]->setIconSize(size);
}

void Client::clearShip(){

    QVector<Cell>::iterator it=boardPlayer->ship->begin();

    int i,j;
    for(; it!=boardPlayer->ship->end();++it){

       i= it->x-1;
       j= it->y-1;
       yourButtons[i][j]->setIcon(QIcon());
    }
    //чистим вектор
     boardPlayer->ship->clear();
     ui->infoLabel->setText("Sorry, choose the other ship.");
}

void Client::blockShip(){

    QVector<Cell>::iterator it=boardPlayer->ship->begin();

    int i,j;
    qDebug() << "Your ship:";
    for(; it!=boardPlayer->ship->end();++it){

       i= it->x-1;
       j= it->y-1;
       qDebug()<<i<<' '<<j;
       yourButtons[i][j]->setEnabled(false);
       boardPlayer->board[i+1][j+1]=boardPlayer->k;
    }
    //чистим вектор
     boardPlayer->ship->clear();
}

void Client::endPlaceSlot(){
    //emit boardPlayer->needBlockField1();
    blockBothFields();
    state=Making_Step;
    ui->infoLabel->setText("Wait for your enemy!");
    SendToServer("ready", -1, -1);
}

void Client::autoBuildFlot()
{
    ui->autoBuild->setEnabled(false);
    boardPlayer->SetShips();
    blockBothFields();
    state=Making_Step;
    ui->infoLabel->setText("Wait for your enemy!");
    SendToServer("ready", -1, -1);
}

void Client::blockBothFields()
{
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            yourButtons[i][j]->setEnabled(false);
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            enemyButtons[i][j]->setEnabled(false);
}

void Client::blockYourField()
{
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            yourButtons[i][j]->setEnabled(false);
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            enemyButtons[i][j]->setEnabled(true);
}

void Client::blockEnemyField()
{
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            yourButtons[i][j]->setEnabled(true);
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            enemyButtons[i][j]->setEnabled(false);
}

void Client::blockField1()
{
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            yourButtons[i][j]->setEnabled(false);
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            enemyButtons[i][j]->setEnabled(true);
}

void Client::blockField2()
{
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
            enemyButtons[i][j]->setEnabled(false);
}

void Client::enemyBoner(int i, int j)
{
    enemyButtons[i-1][j-1]->setIcon(*past);

}

//только установка картинки мимо, вызывается из килл
void Client::setBoner(int i, int j)
{
    yourButtons[i-1][j-1]->setIcon(*past);
    SendToServer("bonerPic", i, j);
}

void Client::youBoner(int i, int j)
{
    yourButtons[i-1][j-1]->setIcon(*past);
    SendToServer("boner", i, j);
}
void Client::enemyHit(int i, int j)
{
    int ii=i-1;
    int jj=j-1;

    enemyButtons[ii][jj]->setIcon(*shipHit);
    enemyButtons[ii][jj]->setIconSize(size);
    //enemyButtons[ii][jj]->setEnabled(false);
    if (i-1!=0 && i-1!=11 && j-1!=0 && j-1!=11)
    {
        enemyButtons[ii-1][jj-1]->setIcon(*past);
        //enemyButtons[ii-1][jj-1]->setEnabled(false);
    }
    if (i-1!=0 && i-1!=11 && j+1!=0 && j+1!=11)
    {
        enemyButtons[ii-1][jj+1]->setIcon(*past);
        //enemyButtons[ii-1][jj+1]->setEnabled(false);
    }
    if (i+1!=0 && i+1!=11 && j-1!=0 && j-1!=11)
    {
        enemyButtons[ii+1][jj-1]->setIcon(*past);
       // enemyButtons[ii+1][jj-1]->setEnabled(false);
    }
    if (i+1!=0 && i+1!=11 && j+1!=0 && j+1!=11)
    {
        enemyButtons[ii+1][jj+1]->setIcon(*past);
       // enemyButtons[ii+1][jj+1]->setEnabled(false);
    }
}
void Client::youHit(int i, int j)
{
    int ii=i-1;
    int jj=j-1;

    SendToServer("hit", i, j);

    yourButtons[ii][jj]->setIcon(*shipHit);
    yourButtons[ii][jj]->setIconSize(size);

    if (i-1!=0 && i-1!=11 && j-1!=0 && j-1!=11)yourButtons[ii-1][jj-1]->setIcon(*past);
    if (i-1!=0 && i-1!=11 && j+1!=0 && j+1!=11)yourButtons[ii-1][jj+1]->setIcon(*past);
    if (i+1!=0 && i+1!=11 && j-1!=0 && j-1!=11)yourButtons[ii+1][jj-1]->setIcon(*past);
    if (i+1!=0 && i+1!=11 && j+1!=0 && j+1!=11)yourButtons[ii+1][jj+1]->setIcon(*past);
}
void Client::enemyKill(int i, int j)
{
    enemyButtons[i-1][j-1]->setIcon(*kill);
    enemyButtons[i-1][j-1]->setIconSize(size);
    //enemyButtons[i-1][j-1]->setEnabled(false);
}
void Client::youKill(int i, int j)
{
    SendToServer("kill", i, j);

    yourButtons[i-1][j-1]->setIcon(*shipHit);
}

void Client::endGame()
{

    blockBothFields();
    ui->infoLabel->setText("You lost, try again!");
    SendToServer("end", -1, -1);

    emit endGameWin(false);

}

void Client::labelOneDesk()
{
    ui->infoLabel->setText("Choose your one-desk ship.");
}
void Client::labelTwoDesk()
{
    ui->infoLabel->setText("Choose your two-desk ship.");
}
void Client::labelThreeDesk()
{
    ui->infoLabel->setText("Choose your three-desk ship.");
}
void Client::labelFourDesk()
{
    ui->infoLabel->setText("Choose your four-desk ship.");
}

void Client::playAgain()
{
   // if (boardPlayer->sum < 20) SendToServer("new game", -1, -1);
    ui->autoBuild->setEnabled(true);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            boardPlayer->board[i][j]=0;
        }
    for (int i=0; i<n-2; i++)
        for (int j=0; j<n-2; j++)
        {
            yourButtons[i][j]->setIcon(QIcon());
            yourButtons[i][j]->setIconSize(size);
            enemyButtons[i][j]->setIcon(QIcon());
            enemyButtons[i][j]->setIconSize(size);
        }
    for (int i=0; i<n-2; i++)
    {
        boardPlayer->flot[i].setHit(0);
        boardBot->flot[i].setHit(0);
    }
    boardPlayer->ship->clear();
    boardPlayer->sum=0;
    boardPlayer->k=1;
    state=Placing_Ships;
    ui->infoLabel->setText("Let`s build your flot! Choose one-desk ship.");
    blockEnemyField();
}

void Client::setStyle()
{
    for (int i=0; i<n-2; i++)
    {
        for (int j=0; j<n-2; j++)
        {
            if (boardPlayer->board[i+1][j+1]==-1)
                yourButtons[i][j]->setIcon(*shipHit);
            if (boardPlayer->board[i+1][j+1]==-2)
                yourButtons[i][j]->setIcon(*past);
            if (boardPlayer->board[i+1][j+1]==-3)
                yourButtons[i][j]->setIcon(*kill);
            if (boardPlayer->board[i+1][j+1]>0)
                yourButtons[i][j]->setIcon(*button);

            yourButtons[i][j]->setIconSize(size);

            if (boardBot->board[i+1][j+1]==-1)
                enemyButtons[i][j]->setIcon(*shipHit);
            if (boardBot->board[i+1][j+1]==-2)
                enemyButtons[i][j]->setIcon(*past);
            if (boardBot->board[i+1][j+1]==-3)
                enemyButtons[i][j]->setIcon(*kill);

            enemyButtons[i][j]->setIconSize(size);
        }
    }
}
