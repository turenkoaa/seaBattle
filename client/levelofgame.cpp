#include "levelofgame.h"
#include "ui_levelofgame.h"

LevelOfGame::LevelOfGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelOfGame)
{
    ui->setupUi(this);
}

LevelOfGame::~LevelOfGame()
{
    delete ui;
}
