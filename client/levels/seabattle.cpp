#include "seabattle.h"
#include "ui_seabattle.h"


SeaBattle::SeaBattle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SeaBattle),
    currentWidget(nullptr)
{
    ui->setupUi(this);

   setMainWidget(1);

    widget = new Widget();
    level = new LevelWidget();
    rules = new Help();
    about = new About();

        widgetsHash.insert(1, level);
        widgetsHash.insert(2, widget);


    pixmap = new QPixmap("C:/QtProjects/seaBattle/field1.jpg");
    this->setFixedSize(pixmap->size());


    QPalette pall;
    pall.setBrush(this->backgroundRole(),QBrush(*pixmap));
    pall.setBrush(widget->backgroundRole(),QBrush(*pixmap));
    pall.setBrush(level->backgroundRole(),QBrush(*pixmap));
    widget->setFixedSize(pixmap->size());

    this->setPalette(pall);
    this->setAutoFillBackground(true);

    //this->setCentralWidget(level);

    kill = new QPixmap("C:/QtProjects/seaBattle/ship1kill.png");
    past = new QPixmap("C:/QtProjects/seaBattle/ship1past.png");
    button = new QPixmap("C:/QtProjects/seaBattle/ship1.png");
    shipHit = new QPixmap("C:/QtProjects/seaBattle/ship1hit.png");

    widget->kill=kill;
    widget->past=past;
    widget->button=button;
    widget->shipHit=shipHit;

    color = QColor(12, 65, 17, 100);
    widget->color = color;

//уровни
    QObject::connect(level->easy, SIGNAL(clicked()), this, SLOT(setMainWidgetSlot()));
    QObject::connect(this, SIGNAL(setWidget(int,bool)), this, SLOT(setMainWidgetSlot(int,bool)));
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
    QObject::connect(this->ui->New_game, SIGNAL(triggered()),this, SLOT(newGame()));
//вкладка помощь
    QObject::connect(this->ui->Rules, SIGNAL(triggered()), this, SLOT(showRules()));
    QObject::connect(this->ui->About_the_auther, SIGNAL(triggered()), this, SLOT(showAbout()));
//стили
    QObject::connect(this->ui->actionSea, SIGNAL(triggered()), this, SLOT(styleSea()));
    QObject::connect(this->ui->actionBoard, SIGNAL(triggered()), this, SLOT(styleBoard()));
    QObject::connect(this->ui->actionDefault, SIGNAL(triggered()), this, SLOT(styleDefault()));
}
SeaBattle::~SeaBattle()
{
    delete ui;
}

void SeaBattle::setMainWidgetSlot()
{
    emit setWidget(2, false);
}


void SeaBattle::setMainWidgetSlot(int idWidget, bool deleteFlag) {

    AbstractWidget* buffer = currentWidget;

    if(deleteFlag) {
        currentWidget = nullptr;
    }

    setMainWidget(idWidget);

    if(deleteFlag && buffer != nullptr) {
        delete buffer;
    }
}

void SeaBattle::setMainWidget(int idWidget) {

    // Очищаем старые сигнально - слотовые соединения
    if(currentWidget) {
        disconnect(currentWidget, SIGNAL(changeCurrentWidget(int,bool)), this, SLOT(setMainWidgetSlot(int,bool)));
    }

    // Получаем виджет по айди
    currentWidget = getWidgetById(idWidget);
    currentWidget->setVisible(true);

    // Делаем виджет центральным для этого окна
    setCentralWidget(currentWidget);

    connect(currentWidget, SIGNAL(changeCurrentWidget(int,bool)), SLOT(setMainWidgetSlot(int,bool)));
}

AbstractWidget* SeaBattle::getWidgetById(int idWidget) {

    // Проверка на наличие виджета в таблице
    if(widgetsHash.contains(idWidget) && widgetsHash[idWidget] != nullptr) {
        return widgetsHash[idWidget];
    }

    AbstractWidget* returnWidget = nullptr;

    // Возвращаем нужный инстанс
    switch(idWidget) {

        case 1:
            returnWidget = new LevelWidget(this);
            break;

        case 2:
            returnWidget = new Widget(this);
            break;
    }

    return returnWidget;
}

void SeaBattle::setLevel()
{
    //setMainWidget(2);
    //this->setCentralWidget(widget);

    //level=new LevelWidget();
    //qDebug() << "ok widget";

}

void SeaBattle::newGame()
{
    emit widget->letsAgain();
    setMainWidget(1);
    qDebug() << "ok";

}

void SeaBattle::showRules()
{
    rules->show();
}
void SeaBattle::showAbout()
{
    about->show();
}

void SeaBattle::styleSea()
{
     pixmap = new QPixmap("C:/QtProjects/seaBattle/field3.png");
     QPalette pall;
     pall.setBrush(this->backgroundRole(),QBrush(*pixmap));
     this->setPalette(pall);

     kill = new QPixmap("C:/QtProjects/seaBattle/ship3kill.png");
     past = new QPixmap("C:/QtProjects/seaBattle/ship3past.png");
     button = new QPixmap("C:/QtProjects/seaBattle/ship3.png");
     shipHit = new QPixmap("C:/QtProjects/seaBattle/ship3hit.png");

     widget->kill=kill;
     widget->past=past;
     widget->button=button;
     widget->shipHit=shipHit;

     emit widget->styleSea();
}

void SeaBattle::styleBoard()
{
     pixmap = new QPixmap("C:/QtProjects/seaBattle/field2.jpg");
     QPalette pall;
     pall.setBrush(this->backgroundRole(),QBrush(*pixmap));
     this->setPalette(pall);

     kill = new QPixmap("C:/QtProjects/seaBattle/ship2kill.png");
     past = new QPixmap("C:/QtProjects/seaBattle/ship2past.png");
     button = new QPixmap("C:/QtProjects/seaBattle/ship2.png");
     shipHit = new QPixmap("C:/QtProjects/seaBattle/ship2hit.png");

     widget->kill=kill;
     widget->past=past;
     widget->button=button;
     widget->shipHit=shipHit;

     emit widget->styleSea();
}

void SeaBattle::styleDefault()
{
     pixmap = new QPixmap("C:/QtProjects/seaBattle/field1.jpg");
     QPalette pall;
     pall.setBrush(this->backgroundRole(),QBrush(*pixmap));
     this->setPalette(pall);

     kill = new QPixmap("C:/QtProjects/seaBattle/ship1kill.png");
     past = new QPixmap("C:/QtProjects/seaBattle/ship1past.png");
     button = new QPixmap("C:/QtProjects/seaBattle/ship1.png");
     shipHit = new QPixmap("C:/QtProjects/seaBattle/ship1hit.png");

     widget->kill=kill;
     widget->past=past;
     widget->button=button;
     widget->shipHit=shipHit;

     emit widget->styleSea();
}
