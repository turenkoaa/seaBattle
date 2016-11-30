#include "client.h"

Client::Client(QTcpSocket* socket, int id):  hasEnemy(false), ready(false), id(id), enemyId(-1), name(-10) //, enemySocket(NULL)
{
    clientSocket = new QTcpSocket();
    clientSocket = socket;
}

QTcpSocket* Client::getClientSocket()
{
    return clientSocket;
}

Client::~Client()
{
    delete clientSocket;
}

void Client::disconnected()
{
    emit deleteClient(id);
}
