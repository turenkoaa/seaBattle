#include "disconnectionpage.h"
#include "ui_disconnectionpage.h"

DisconnectionPage::DisconnectionPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisconnectionPage)
{
    ui->setupUi(this);
}

DisconnectionPage::~DisconnectionPage()
{
    delete ui;
}
