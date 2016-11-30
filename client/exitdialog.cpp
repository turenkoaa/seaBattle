#include "exitdialog.h"
#include "ui_exitdialog.h"

ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);


    QPixmap* pixmap = new QPixmap("C:/Users/HP/Desktop/Sea Battle/client/pictures/endOfGame.jpg");
    this->setFixedSize(pixmap->size());

    QPalette pall;
    pall.setBrush(this->backgroundRole(),QBrush(*pixmap));
    this->setPalette(pall);
    this->setAutoFillBackground(true);

}

ExitDialog::~ExitDialog()
{
    delete ui;
}

void ExitDialog::slotChangeLableWin(bool win)
{
   if (win) ui->winOrLost->setText("You won! Conratulations!");
   else ui->winOrLost->setText("You lost, don`t worry!");
}


