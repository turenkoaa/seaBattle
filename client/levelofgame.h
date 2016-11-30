#ifndef LEVELOFGAME_H
#define LEVELOFGAME_H

#include <QWidget>

namespace Ui {
class LevelOfGame;
}

class LevelOfGame : public QWidget
{
    Q_OBJECT

public:
    explicit LevelOfGame(QWidget *parent = 0);
    ~LevelOfGame();

private:
    Ui::LevelOfGame *ui;
};

#endif // LEVELOFGAME_H
