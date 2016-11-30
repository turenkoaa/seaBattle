#include "startpage.h"
#include "ui_startpage.h"

StartPage::StartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPage)
{
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
    ui->startButton_2->setEnabled(false);
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(slotStartClicked()));
    connect(ui->startButton_2, SIGNAL(clicked()), this, SLOT(slotPlayWithBot()));
    //connect(ui->inputName, SIGNAL(returnPressed()), this, SLOT(slotGetName()));
}

StartPage::~StartPage()
{
    delete ui;
}

void StartPage::connected(){

    ui->startButton->setEnabled(true);
    ui->label_3->setText("New enemy is ready for battle, start game!");
}

/*void StartPage::slotGetName()
{
    ui->startButton->setEnabled(true);
}*/

void StartPage::slotStartClicked()
{
   /* if (ui->inputName->text() != "")
        emit signStartClicked(ui->inputName->text());*/

    emit signStartClicked();
}

void StartPage::slotChangeStart(int flag)
{
    ui->startButton->setEnabled(false);
    ui->label_3->setText("Please, wait for you enemy`s connection.");

    if (flag == 1) ui->label_2->setText("Your enemy has left the game.");
    else if (flag == 2) ui->label_2->setText("Welcome to a new game!");
}

void StartPage::slotPlayWithBot()
{
    emit signPlayWithBot();
}
