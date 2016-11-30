#ifndef WIDGET_H
#define WIDGET_H

//#include "Board.h"
//#include "levelofgame.h"

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
/*#include <QBoxLayout>
#include <QDebug>
#include <QVector>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QPixmap>


namespace Ui {
class Widget;
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

class Widget : public QWidget
{
    Q_OBJECT

public:
    //массив точек поля
    Point*** points;

    QPixmap *kill, *past, *button, *shipHit, *pixmap;
    const QSize size;
    Level level;
    QColor color;
    Ui::Widget *ui;
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:

    State state;
    QPushButton ***yourButtons, ***enemyButtons;
    Board *boardPlayer, *boardBot;

public slots:

    void buttonPressed(int,int);

    //слот завершения игры
    void endGame(Board*);

    //слот стирающий корабль
    void clearShip();
    void blockField1();
    void blockField2();
    void blockShip();
    void endPlaceSlot();
    void enemyAttack();
    void enemyBoner(int,int);
    void youBoner(int,int);
    void enemyHit(int,int);
    void youHit(int,int);
    void enemyKill(int,int);
    void youKill(int,int);
 //   void againButtonChecked();
    void labelOneDesk();
    void labelTwoDesk();
    void labelThreeDesk();
    void labelFourDesk();
    void playAgain();
    void setEasyLevel();
    void setVeryEasyLevel();
    void setMediumLevel();
    void setHardLevel();
    void setVeryHardLevel();
    void setStyle();

signals:
    void waitingStep();
    void letsAgain();
    void styleSea();

};


#endif // WIDGET_H

*/
