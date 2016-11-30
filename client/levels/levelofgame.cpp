#include "levelofgame.h"
#include "ui_levelofgame.h"

LevelOfGame::LevelOfGame(QWidget *parent) :
   // AbstractWidget(parent),
    QMainWindow(parent),
    ui(new Ui::LevelOfGame)
{
    ui->setupUi(this);
    easy=ui->easyButton;
    veryEasy=ui->veryEasyButton;
    medium=ui->mediumButton;
    hard=ui->hardButton;
    veryHard=ui->veryHardButton;
}

LevelOfGame::~LevelOfGame()
{
    delete ui;
}
