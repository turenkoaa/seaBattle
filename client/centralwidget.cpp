#include "centralwidget.h"
#include "ui_centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CentralWidget)
{
    ui->setupUi(this);

    client = new Client("localhost", 2323, this);
    start = new StartPage(this);
    disconnect = new DisconnectionPage(this);
    chooseEnemy = new ChooseEnemyPage(this);
    rules = new Help();
    about = new About();
    exitDialog = new ExitDialog();
    level = new LevelOfGame();

    client->hide();
    start->hide();
    disconnect->hide();
    chooseEnemy->hide();
    level->hide();
    exitDialog->setModal(true);

    pixmap1 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/field1.jpg");
    kill1 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship1kill.png");
    past1 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship1past.png");
    button1 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship1.png");
    shipHit1 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship1hit.png");

    pixmap3 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/field3.png");
    kill3 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship3kill.png");
    past3 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship3past.png");
    button3 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship3.png");
    shipHit3 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship3hit.png");

    pixmap2 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/field2.jpg");
    kill2 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship2kill.png");
    past2 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship2past.png");
    button2 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship2.png");
    shipHit2 = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/ship2hit.png");


    this->setFixedSize(pixmap1->size());
    client->setFixedSize(pixmap1->size());
    start->setFixedSize(pixmap1->size());
    disconnect->setFixedSize(pixmap1->size());


    QPalette pall;
    pall.setBrush(this->backgroundRole(),QBrush(*pixmap1));
    this->setPalette(pall);
    this->setAutoFillBackground(true);

    client->kill=kill1;
    client->past=past1;
    client->button=button1;
    client->shipHit=shipHit1;

    color = QColor(12, 65, 17, 100);
    client->color = color;

    connect(client, SIGNAL(signalDisconnected()), this, SLOT(errorConnection()));
    connect(client, SIGNAL(signalConnected()), this, SLOT(hasConnection()));
    connect(client, SIGNAL(signalFindEnemy()), start, SLOT(connected()));

    connect(start, SIGNAL(signStartClicked()), this, SLOT(startGame()));

    //connect(start, SIGNAL(signStartClicked(QString)), client, SLOT(slotSendName(QString)));
    //connect(start, SIGNAL(signStartClicked(QString)), this, SLOT(slotChooseEnemy(QString)));

    connect(client, SIGNAL(needNewEnemy(int)), this, SLOT(findNewEnemy(int)));
    connect(this, SIGNAL(changeStartPage(int)), start, SLOT(slotChangeStart(int)));
    connect(client, SIGNAL(endGameWin(bool)), this, SLOT(slotEndGame(bool)));
    connect(client, SIGNAL(endGameWin(bool)), exitDialog, SLOT(slotChangeLableWin(bool)));
    connect(exitDialog, SIGNAL(accepted()), this, SLOT(slotEndGame()));
    connect(this, SIGNAL(signNewGame()), client, SLOT(slotNewGame()));
    connect(this, SIGNAL(signEndGame()), client, SLOT(slotEndGame()));

    connect(start, SIGNAL(signPlayWithBot()), this, SLOT(slotChooseLevel()));

/*
//уровни
    QObject::connect(level->easy, SIGNAL(clicked()), this, SLOT(setLevel()));
    QObject::connect(level->easy, SIGNAL(clicked()), widget,SLOT(setEasyLevel()));

    QObject::connect(level->veryEasy, SIGNAL(clicked()), this, SLOT(setLevel()));
    QObject::connect(level->veryEasy, SIGNAL(clicked()), widget,SLOT(setVeryEasyLevel()));

    QObject::connect(level->medium, SIGNAL(clicked()), this, SLOT(setLevel()));
    QObject::connect(level->medium, SIGNAL(clicked()), widget,SLOT(setMediumLevel()));

    QObject::connect(level->hard, SIGNAL(clicked()), this, SLOT(setLevel()));
    QObject::connect(level->hard, SIGNAL(clicked()), widget,SLOT(setHardLevel()));

    QObject::connect(level->veryHard, SIGNAL(clicked()), this, SLOT(setLevel()));
    QObject::connect(level->veryHard, SIGNAL(clicked()), widget,SLOT(setVeryHardLevel()));
//вкладка новая игра
    QObject::connect(this->ui->New_game, SIGNAL(triggered()),this, SLOT(resetThisSlot()));
//вкладка помощь
    QObject::connect(this->ui->Rules, SIGNAL(triggered()), this, SLOT(showRules()));
    QObject::connect(this->ui->About_the_auther, SIGNAL(triggered()), this, SLOT(showAbout()));*/

}

void CentralWidget::slotChooseLevel()
{
    start->hide();
    level->show();
}

void CentralWidget::slotNewGame()
{
    findNewEnemy(2);
    emit signNewGame();
}

void CentralWidget::slotEndGame()
{
    findNewEnemy(2);
    emit signEndGame();
}

CentralWidget::~CentralWidget()
{
    delete ui;
    delete client;
    delete start;
    delete disconnect;
    delete chooseEnemy;
}

void CentralWidget::slotChooseEnemy(QString str)
{
    start->hide();
    chooseEnemy->show();
}

void CentralWidget::errorConnection()
{
    start->hide();
    client->hide();
    chooseEnemy->hide();
    disconnect->show();
}

void CentralWidget::startGame()
{
    start->hide();
    client->show();
}

void CentralWidget::hasConnection()
{
    start->show();
    qDebug() << "подключение прошло успешно";
}

void CentralWidget::findNewEnemy(int flag)
{
   emit changeStartPage(flag);
   client->hide();
   if (start->isHidden()) start->show();

}

void CentralWidget::showRules()
{
    rules->show();
}
void CentralWidget::showAbout()
{
    about->show();
}

void CentralWidget::slotEndGame(bool win)
{
    exitDialog->show();

}

/*
void SeaBattle::setLevel()
{
    this->setCentralWidget(widget);
    //level = new LevelOfGame();

}


void SeaBattle::newGame()
{
    //emit widget->letsAgain();
    //this->centralWidget()->close();
    level = new LevelOfGame();
    this->setCentralWidget(level);
    widget = new Widget();


    qDebug() << "ok";

}



*/

void CentralWidget::styleSea()
{
     QPalette pall;
     pall.setBrush(this->backgroundRole(),QBrush(*pixmap3));
     this->setPalette(pall);

     client->kill=kill3;
     client->past=past3;
     client->button=button3;
     client->shipHit=shipHit3;

     emit client->styleSea();
}

void CentralWidget::styleBoard()
{
     QPalette pall;
     pall.setBrush(this->backgroundRole(),QBrush(*pixmap2));
     this->setPalette(pall);

     client->kill=kill2;
     client->past=past2;
     client->button=button2;
     client->shipHit=shipHit2;

     emit client->styleSea();
}

void CentralWidget::styleDefault()
{
     QPalette pall;
     pall.setBrush(this->backgroundRole(),QBrush(*pixmap1));
     this->setPalette(pall);

     client->kill=kill1;
     client->past=past1;
     client->button=button1;
     client->shipHit=shipHit1;

     emit client->styleSea();
}


