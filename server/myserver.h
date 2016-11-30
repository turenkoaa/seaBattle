#ifndef MYSERVER_H
#define MYSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>

#include <client.h>

class MyServer : public QWidget {
Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    QTextEdit*  m_ptxt;
    quint16     m_nNextBlockSize;
    QHash<int, Client*> clients;

    void sendToClient(QTcpSocket*, const QString&, int, int);
    void newEnemy(int);
    int findEnemy(int);

public:
    MyServer(int nPort, QWidget* pwgt = 0);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
            void pricessRequest(int, QString, int, int);
            void slotDeleteUser(int);
};
#endif // MYSERVER_H
