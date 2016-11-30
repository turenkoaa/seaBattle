#ifndef CHOOSEENEMYPAGE_H
#define CHOOSEENEMYPAGE_H

#include <QWidget>

namespace Ui {
class ChooseEnemyPage;
}

class ChooseEnemyPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseEnemyPage(QWidget *parent = 0);
    ~ChooseEnemyPage();
private:
    Ui::ChooseEnemyPage *ui;
    QString enemyName;

private slots:
    //void enemyHasChoosen(QListWidgetItem*);
    void startGame();

signals:
    void signEnemyHasChoosen(QString);
};

#endif // CHOOSEENEMYPAGE_H
