#include "levelwidget.h"
#include "ui_levelwidget.h"

LevelWidget::LevelWidget(QWidget *parent) :
    //QWidget(parent),
    AbstractWidget(parent),
    ui(new Ui::LevelWidget)

{
    ui->setupUi(this);
    easy=ui->easyButton;
    veryEasy=ui->veryEasyButton;
    medium=ui->mediumButton;
    hard=ui->hardButton;
    veryHard=ui->veryHardButton;
}

LevelWidget::~LevelWidget()
{
    delete ui;
}
