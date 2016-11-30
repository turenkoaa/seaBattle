#include "seabattle.h"
#include "ui_seabattle.h"

SeaBattle::SeaBattle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SeaBattle)
{
    ui->setupUi(this);
    centralWidget = new CentralWidget();
    rules = new Help();
    about = new About();

    this->setCentralWidget(centralWidget);
    QPixmap* pixmap = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/field1.jpg");
    this->setFixedSize(pixmap->size());

    //вкладка помощь
    connect(this->ui->Rules, SIGNAL(triggered()), this, SLOT(showRules()));
    connect(this->ui->About_the_author, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(this->ui->actionSea, SIGNAL(triggered()), centralWidget, SLOT(styleSea()));
    connect(this->ui->actionBoard, SIGNAL(triggered()), centralWidget, SLOT(styleBoard()));
    connect(this->ui->actionDefault, SIGNAL(triggered()), centralWidget, SLOT(styleDefault()));
    connect(this->ui->New_game, SIGNAL(triggered()), centralWidget, SLOT(slotNewGame()));

    connect(centralWidget->exitDialog, SIGNAL(rejected()), this, SLOT(close()));
    connect(centralWidget->exitDialog, SIGNAL(destroyed()), this, SLOT(close()));
}
SeaBattle::~SeaBattle()
{
    delete ui;
}

void SeaBattle::showRules()
{
    rules->show();
}
void SeaBattle::showAbout()
{
    about->show();
}


