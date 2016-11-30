#ifndef PLAYER_H
#define PLAYER_H

#include <QTime>
#include <QObject>
#include <QVector>
#include <QDebug>

const int n = 12;

//enum Level
//{
//    very_easy, easy, medium, hard, very_hard
//};

class Cell
{
public:
    int x, y;
    Cell();
    Cell(int x, int y);
};


class Ship
{

public:
    Ship();
    int getHit();
    void setHit();
    void setHit(int n);
    int getDesks();
    void setDesks(int number);

private:
    int desks, hit;
};

class Player : public QObject{
    Q_OBJECT

public:
      Player();
        int getSum();
        int getBoardEl(int i, int j);
        bool Suitable1(Cell c);
        bool Suitable(int m, QVector<Cell> *cell);
        void GetShips(Cell cell);
        void SetShips();
        void Hit(int i, int j);
        void Kill(int i, int j);
        void Boner(int i, int j);
        //Cell autoAttack(Level);
        void checkAttack(Cell cell);
        //номер создаваемого корабля
        int k;
        int num;
        //точки создаваемого корабля
        QVector<Cell>* ship;

 public:
 int board[n][n];
 int sum;
 Ship flot[n - 2];
     ~Player();


signals:
 void endGame();
 void needClear();
 void needBlock();
 void needBlockField1();
 void needBlockField2();
 //сигнал конца построения флота ее величества
 void endPlace();
 void signBonerPic(int, int);
 void signBoner(int, int);
 void signHit(int, int);
 void signKill(int, int);
 void signShip(int, int);
 void oneDeskShip();
 void twoDeskShip();
 void threeDeskShip();
 void fourDeskShip();
 void nextTurn();
 //void needChangeCells();

};


#endif // PLAYER_H
