#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>

#include "Player.h"

namespace Ui {
class client;
}

enum State
{
    Placing_Ships, Making_Step
};

class Point : public QObject{
   Q_OBJECT

private:
    int i,j;
public:
    Point(int, int);
public slots:
    void toResiveASignal();
signals:
    void reciveCoordinates(int, int);
};



class Client : public QWidget
{
    Q_OBJECT

private:
    Ui::client *ui;
    quint16 m_nNextBlockSize;
    QTcpSocket* m_pTcpSocket;
    State state;
    QPushButton ***yourButtons, ***enemyButtons;
    Player *boardPlayer, *boardBot;
    QString name;

    void SendToServer(QString , int, int);
    void checkAnswer(QString, int, int);


public:
    //массив точек поля
    Point*** points;

    QPixmap *kill, *past, *button, *shipHit, *pixmap;
    const QSize size;
    //Level level;
    QColor color;

    explicit Client(const QString &strHost, int nPort, QWidget *parent = 0);
    ~Client();
     void playAgain();


private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    //void slotSendToServer();

    void slotConnected();

    void buttonPressed(int,int);

    //слот завершения игры
    void endGame();

    //слот стирающий корабль
    void clearShip();
    void blockField1();
    void blockField2();
    void blockShip();
    void endPlaceSlot();

    void blockBothFields();
    void blockYourField();
    void blockEnemyField();


   // void enemyAttack();
    void setBoner(int i, int j);
    void enemyBoner(int,int);
    void youBoner(int,int);
    void enemyHit(int,int);
    void youHit(int,int);
    void enemyKill(int,int);
    void youKill(int,int);

    void labelOneDesk();
    void labelTwoDesk();
    void labelThreeDesk();
    void labelFourDesk();

    //void setEasyLevel();
   // void setVeryEasyLevel();
   // void setMediumLevel();
   // void setHardLevel();
   // void setVeryHardLevel();
    void setStyle();
    void slotSendName(QString);
    void slotNewGame();
    void slotEndGame();

    void autoBuildFlot();
    void slotSetShip(int, int);

signals:
    void waitingStep();
    void letsAgain();
    void styleSea();

    void signalConnected();
    void signalDisconnected();
    void signalFindEnemy();
    void needNewEnemy(int);
    void endGameWin(bool);

};

#endif // CLIENT_H
