#ifndef CLIENT_H
#define CLIENT_H

#include "QTcpSocket"

class Client: public QObject
{
    Q_OBJECT
public:
    Client(QTcpSocket *, int);
    ~Client();

    bool hasEnemy;
    bool ready;
    int id;
    int enemyId;
    QString name;
    QTcpSocket* getClientSocket();

private:
    QTcpSocket* clientSocket;

public slots:
    void disconnected();

signals:
    void deleteClient(int);

};


#endif // CLIENT_H
