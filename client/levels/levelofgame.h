#ifndef LEVELOFGAME_H
#define LEVELOFGAME_H

#include <QMainWindow>
#include <QPushButton>

#include "AbstractWidget.h"

namespace Ui {
class LevelOfGame;
}

class LevelOfGame :
        public QMainWindow
{
    Q_OBJECT

public:
    explicit LevelOfGame(QWidget *parent = 0);
    ~LevelOfGame();


    Ui::LevelOfGame *ui;
    QPushButton* easy, *veryEasy, *medium, *hard, *veryHard;


};

#endif // LEVELOFGAME_H
