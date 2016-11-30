#ifndef PLAYERS_H
#define PLAYERS_H

#include <QWidget>

class Players: public QWidget{

   Q_OBJECT

private:
    int idUser1;
    int idUser2;

public:
    Players(QWidget* pwgt = 0 /*=0*/);
    bool addPlayer(int);
    int getEnemyOf(int);

signals:
    void enemiesAreReady();

};

#endif // PLAYERS_H


