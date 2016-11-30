#include "Players.h"

Players::Players(QWidget *pwgt): idUser1(0), idUser2(0){}

bool Players::addPlayer(int id)
{
   if (idUser1 == 0)
        { idUser1 = id; return true; }
   else if (idUser2 == 0)
        { idUser2 = id; emit enemiesAreReady(); return true; }
   else  return false;

}

int Players::getEnemyOf(int id)
{
    return (id == isUser1) ? idUser2 : idUser1;
}


