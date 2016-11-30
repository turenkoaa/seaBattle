#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>
#include <QPushButton>

#include "AbstractWidget.h"

namespace Ui {
class LevelWidget;
}

class LevelWidget :
        //public QWidget
        public AbstractWidget
{
    Q_OBJECT

public:
    explicit LevelWidget(QWidget *parent = 0);
    ~LevelWidget();


    Ui::LevelWidget *ui;
    QPushButton* easy, *veryEasy, *medium, *hard, *veryHard;
};

#endif // LEVELWIDGET_H
