#include "chooseenemypage.h"
#include "ui_chooseenemypage.h"

ChooseEnemyPage::ChooseEnemyPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseEnemyPage)
{
    ui->setupUi(this);
    ui->chooseButton->setEnabled(false);

    connect(ui->listOfEnemies, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(enemyHasChoosen(QListWidgetItem*)));
    connect(ui->chooseButton, SIGNAL(clicked()), this, SLOT(startGame()));
}

ChooseEnemyPage::~ChooseEnemyPage()
{
    delete ui;
}


/*void ChooseEnemyPage::enemyHasChoosen(QListWidgetItem * enemy)
{
    ui->setEnabled(true);
    enemyName = enemy->text();
}
*/
void ChooseEnemyPage::startGame()
{
    emit signEnemyHasChoosen(enemyName);
}
