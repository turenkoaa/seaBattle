#ifndef SEABATTLE_H
#define SEABATTLE_H

#include <QMainWindow>
#include "centralwidget.h"
#include "help.h"
#include "about.h"

namespace Ui {
class SeaBattle;
}

class SeaBattle : public QMainWindow
{
    Q_OBJECT

public:
    explicit SeaBattle(QWidget *parent = 0);
    ~SeaBattle();

private:
    Ui::SeaBattle *ui;
    CentralWidget* centralWidget;
    Help* rules;
    About* about;

private slots:
    void showRules();
    void showAbout();

};
#endif // SEABATTLE_H
