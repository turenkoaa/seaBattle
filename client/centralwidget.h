#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QPushButton>

#include "client.h"
#include "startpage.h"
#include "disconnectionpage.h"
#include "chooseenemypage.h"
//#include "levelofgame.h"
#include "help.h"
#include "about.h"
#include "exitdialog.h"
#include "levelofgame.h"

namespace Ui {
class CentralWidget;
}

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = 0);
    ~CentralWidget();

private:
    Ui::CentralWidget *ui;
    Client* client;
    StartPage* start;
    DisconnectionPage* disconnect;
    ChooseEnemyPage* chooseEnemy;
    LevelOfGame* level;
    Help* rules;
    About* about;
    QPixmap *kill1,*past1, *button1, *shipHit1, *pixmap1;
    QPixmap *kill2,*past2, *button2, *shipHit2, *pixmap2;
    QPixmap *kill3,*past3, *button3, *shipHit3, *pixmap3;
    QColor color;
public:
    ExitDialog* exitDialog;

private slots:
    void errorConnection();
    void hasConnection();
    void startGame();
    void findNewEnemy(int);
    void slotNewGame();
    //void setLevel();
    void showRules();
    void showAbout();
    void slotEndGame(bool);
    void slotEndGame();
    void styleSea();
    void styleBoard();
    void styleDefault();
    void slotChooseEnemy(QString);
    //void resetThisSlot();

    void slotChooseLevel();

signals:
    void resetSeaBattleSignal();
    void changeStartPage(int);
    void signNewGame();
    void signEndGame();
};

#endif // CENTRALWIDGET_H


