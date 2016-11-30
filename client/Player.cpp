#include "Player.h"

Cell::Cell(int x, int y) :x(x), y(y){}
Cell::Cell() :x(0), y(0) {}

Ship::Ship():desks(0), hit(0){}

int Ship::getHit() { return hit; }
void Ship::setHit(){ hit++; return; }
void Ship::setHit(int n) { hit=n; };
int Ship::getDesks(){ return desks; }
void Ship::setDesks(int number){ desks = number; }

Player::Player():k(1),num(0), sum(0)
    {
        ship = new QVector<Cell>;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                board[i][j] = 0;
        for (int i = 0; i < 4; i++)
            flot[i].setDesks(1);
        for (int i = 4; i < 7; i++)
            flot[i].setDesks(2);
        for (int i = 7; i < 9; i++)
            flot[i].setDesks(3);
        flot[9].setDesks(4);
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    }
    int Player::getSum() { return sum; }
    int Player::getBoardEl(int i, int j)
    {
        int Elem;
        if (this->board[i + 1][j + 1] == -2 || this->board[i + 1][j + 1] == -1 || this->board[i + 1][j + 1] == -3)
            Elem = this->board[i + 1][j + 1];
        else Elem = 0;
        return Elem;
    }
    bool Player::Suitable1(Cell c)
    {
        return (board[c.x][c.y] == 0 && board[c.x - 1][c.y] == 0 && board[c.x][c.y + 1] == 0 && board[c.x + 1][c.y] == 0
            && board[c.x][c.y - 1] == 0 && board[c.x - 1][c.y + 1] == 0 && board[c.x - 1][c.y - 1] == 0 && board[c.x + 1][c.y - 1] == 0
            && board[c.x + 1][c.y + 1] == 0);
    }
    bool Player::Suitable(int m, QVector<Cell>* cell)
    {
        int sum1 = 0, sum2 = 0, min, max;
        Cell *cells = new Cell[m];
        for (int i = 0; i < m; i++)
        {
            cells[i].x = cell->at(i).x;
            cells[i].y = cell->at(i).y;
        }
        for (int i = 0; i < m; i++)
            if (board[cells[i].x][cells[i].y] == 0) sum1 += 1;

        if (sum1 < m) return false;

        sum1 = 0;
        for (int i = 0; i < m - 1; i++)
            for (int j = i + 1; j < m; j++)
            {
                if (cells[i].x == cells[j].x && cells[i].y != cells[j].y) { sum1 += 1; }
                sum2 += 1;
            }

        if (sum1 == sum2)
        {
            int &I = cells[0].x;
            min = cells[0].y;
            max = cells[0].y;
            for (int i = 1; i < m; i++)
            {
                if (cells[i].y > max) max = cells[i].y;
                if (cells[i].y < min) min = cells[i].y;
            }
            sum1 = 0;
            sum2 = 0;
            if (max - min > m - 1) return false;
            for (int j = min - 1; j <= max + 1; j++)
            {
                if (board[I - 1][j] == 0) sum1 += 1;
                sum2 += 1;
            }
            if (sum1 < sum2) return false;
            else
            {
                sum1 = 0;
                sum2 = 0;
                for (int j = min - 1; j <= max + 1; j++)
                {
                    if (board[I + 1][j] == 0) sum1 += 1;
                    sum2 += 1;
                }
                if (sum1 < sum2) return false;
                else
                {
                    sum1 = 0;
                    sum2 = 0;
                    for (int i = I - 1; i <= I + 1; i++)
                    {
                        if (board[i][min - 1] == 0) sum1 += 1;
                        sum2 += 1;
                    }
                    if (sum1 < sum2) return false;
                    else
                    {
                        sum1 = 0;
                        sum2 = 0;
                        for (int i = I - 1; i <= I + 1; i++)
                        {
                            if (board[i][max + 1] == 0) sum1 += 1;
                            sum2 += 1;
                        }
                        if (sum1 < sum2) return false;
                        else return true;
                    }

                }
            }
        }
        else
        {
            sum1 = 0;
            sum2 = 0;
            for (int i = 0; i < m - 1; i++)
                for (int j = i + 1; j < m; j++)
                {
                    if (cells[i].y == cells[j].y && cells[i].x != cells[j].x) { sum1 += 1; }
                    sum2 += 1;
                }

            if (sum1 == sum2)
            {
                int &J = cells[0].y;
                min = cells[0].x;
                max = cells[0].x;

                for (int i = 1; i < m; i++)
                {
                    if (cells[i].x > max) max = cells[i].x;
                    if (cells[i].x < min) min = cells[i].x;
                }
                sum1 = 0;
                sum2 = 0;
                if (max - min >m - 1) return false;
                for (int j = min - 1; j <= max + 1; j++)
                {
                    if (board[j][J - 1] == 0) sum1 += 1;
                    sum2 += 1;
                }
                if (sum1 < sum2) return false;
                else
                {
                    sum1 = 0;
                    sum2 = 0;
                    for (int j = min - 1; j <= max + 1; j++)
                    {
                        if (board[j][J + 1] == 0) sum1 += 1;
                        sum2 += 1;
                    }
                    if (sum1 < sum2)return false;
                    else
                    {
                        sum1 = 0;
                        sum2 = 0;
                        for (int i = J - 1; i <= J + 1; i++)
                        {
                            if (board[min - 1][i] == 0) sum1 += 1;
                            sum2 += 1;
                        }
                        if (sum1 < sum2) return false;
                        else
                        {
                            sum1 = 0;
                            sum2 = 0;
                            for (int i = J - 1; i <= J + 1; i++)
                            {
                                if (board[max + 1][i] == 0) sum1 += 1;
                                sum2 += 1;
                            }
                            if (sum1 < sum2) return false;
                            else return true;
                        }
                    }
                }

            }
            else return false;
        }
    }
    void Player::GetShips(Cell cell)
    {
        //QObject::connect(this, SIGNAL(needChangeCells()), this, SLOT(changeCells()));
        int desk=2;
        if (k<5)
        {  ship->push_back(cell);
           emit oneDeskShip();
           if (Suitable1(cell))
            {
               //board[cell.x][cell.y] = k;
               //emit needChangeCells();
               emit needBlock();
               k++;
               if (k==5) emit twoDeskShip();
            }
           else
           {

               qDebug() << "ErrorShip";
               emit needClear();
           }
        }
        else if ((k>4) && (k<8))
        {
            emit twoDeskShip();
            if (ship->size()+1==desk)
            {
                ship->push_back(cell);

                if (Suitable(desk, ship))
                {
                    //board[cell.x][cell.y] = k;

                    //сигнал следующий корабль
                    //emit needChangeCells();
                    emit needBlock();
                    k++;
                    if (k==8) emit threeDeskShip();
                }
                else
                {
                qDebug() << "ErrorShip";
                //сигнал стереть
                emit needClear();
                }
            }
            else if(ship->size()+1<desk)
            {
                ship->push_back(cell);
            }
        }
        else if (k>7 && k<10)
        {
            desk=3;
            emit threeDeskShip();
            if (ship->size()+1==desk)
            {
                ship->push_back(cell);
                if (Suitable(desk, ship))
                {
                    //board[cell.x][cell.y] = k;
                    //сигнал следующий корабль
                    //emit needChangeCells();
                    emit needBlock();
                    k++;
                    if (k==10) emit fourDeskShip();
                }
                else
                {
                qDebug() << "ErrorShip";
                //сигнал стереть
                emit needClear();
                }
            }
            else if(ship->size()+1<desk)
            {
                ship->push_back(cell);
            }
        }
        else if(k==10)
        {
            desk=4;
            emit fourDeskShip();
            if (ship->size()+1==desk)
            {
                ship->push_back(cell);
                if (Suitable(desk, ship))
                {
                    //board[cell.x][cell.y] = k;
                    //сигнал конец построения
                    //emit needChangeCells();
                    emit needBlock();
                    emit endPlace();
                }
                else
                {
                qDebug() << "ErrorShip";
                //сигнал стереть
                emit needClear();
                }
            }
            else if(ship->size()+1<desk)
            {
                ship->push_back(cell);
            }
        }

    }
    void Player::SetShips()
    {
        int size = 1, I, J;
        bool horiz;
        Cell cell;

        for (int number = 10; number >= 5; number--)
        {
            if (number == 5 || number == 6 || number == 7) size = 2;
            if (number == 8 || number == 9) size = 3;
            if (number == 10) size = 4;

            horiz = qrand() % 2 == 0;
            I = 0;
            J = 0;

            QVector<Cell> cells;
            do
            { cells.clear();
                do
                {
                    I = qrand() % n;
                } while (I == 0 || I == 11|| (!horiz && I > n - size -1));
                do
                {
                    J = qrand() % n;
                } while (J == 0 || J == 11 || (horiz && J > n - size -1));
                if (horiz)
                {
                    for (int i = 0; i < size; i++)
                    {

                        //cells->push_back(Cell(I, J+i));

                        cells.push_back(Cell(I, J+i));

                        //cells->at(i).x = I;
                        //cells->at(i).y = J + i;
                    }
                }
                else
                {
                    for (int i = 0; i < size; i++)
                    {
                        //cells->push_back(Cell(I+i, J));

                        cells.push_back(Cell(I+i, J));
                        //cells->at(i).x = I + i;
                        //cells->at(i).y = J;
                    }
                }


            } while (!Suitable(size, &cells));
           // qDebug() << "other ships ok!";
            for (int i = 0; i < size; i++)
            {
                //board[cells->at(i).x][cells->at(i).y] = number;
                board[cells[i].x][cells[i].y] = number;
                emit signShip(cells[i].x - 1, cells[i].y - 1);
            }
        }
        for (int i = 1; i <= 4; i++)
        {
            do
            {
              cell.x = qrand() % n;
              cell.y = qrand() % n;
            } while (cell.x==0 ||cell.y==11 || cell.x==11||cell.y==0 || !Suitable1(cell));
            board[cell.x][cell.y] = i;
            emit signShip(cell.x - 1, cell.y - 1);
        }
        //qDebug() << "one-desk ship ok!";
    }
    void Player::Hit(int i, int j)
    {
        board[i][j] = -1;
        board[i - 1][j - 1] = -2;
        board[i - 1][j + 1] = -2;
        board[i + 1][j - 1] = -2;
        board[i + 1][j + 1] = -2;
        emit signHit(i, j);
        return;
    }
    void Player::Kill(int i, int j)
    {
        Hit(i, j);
        board[i][j] = -3;
        signKill(i, j);
            int k;
            if (board[i][j + 1] == -1 || board[i][j - 1] == -1)
            {
                k = 1;
                while (board[i][j + k] == -1)
                {

                    board[i][j + k] = -3;
                    emit signKill(i, j+k);
                    k++;
                }
                board[i][j + k] = -2;
                if (i!=0 && i!=11 && j+k!=0 && j+k!=11)emit signBonerPic(i, j+k);
                k = 1;
                while (board[i][j - k] == -1)
                {
                    board[i][j - k] = -3;
                    emit signKill(i, j-k);
                    k++;
                }
                board[i][j - k] = -2;
                if (i!=0 && i!=11 && j-k!=0 && j-k!=11)emit signBonerPic(i, j-k);
                return;
            }
            else if (board[i + 1][j] == -1 || board[i - 1][j] == -1)
            {
                k = 1;
                while (board[i + k][j] == -1)
                {
                    board[i + k][j] = -3;
                    emit signKill(i+k, j);
                    k++;
                }
                board[i + k][j] = -2;
                if (i+k!=0 && i+k!=11 && j!=0 && j!=11) emit signBonerPic(i+k, j);
                k = 1;
                while (board[i - k][j] == -1)
                {
                    board[i - k][j] = -3;
                    emit signKill(i-k, j);
                    k++;
                }
                board[i - k][j] = -2;
                if (i-k!=0 && i-k!=11 && j!=0 && j!=11)emit signBonerPic(i-k, j);
                return;
            k = 1;
            }
            else
            {
                board[i][j + 1] = -2;
                if (i!=0 && i!=11 && j+1!=0 && j+1!=11)emit signBonerPic(i, j+1);
                board[i][j - 1] = -2;
                if (i!=0 && i!=11 && j-1!=0 && j-1!=11)emit signBonerPic(i, j-1);
                board[i + 1][j] = -2;
                if (i+1!=0 && i+1!=11 && j!=0 && j!=11)emit signBonerPic(i+1, j);
                board[i - 1][j] = -2;
                if (i-1!=0 && i-1!=11 && j!=0 && j!=11)emit signBonerPic(i-1, j);
            }
            return;
    }
    void Player::Boner(int i, int j)
    {
        board[i][j] = -2;
        emit signBoner(i, j);
    }
   /* Cell Player::autoAttack(Level level)
        {
            Cell cell;

            int I = -1, J, k = 1;

            if (level==very_easy)
            {
                do{
                    cell.x = qrand() % (n - 2);
                    cell.y = qrand() % (n - 2);
                } while (getBoardEl(cell.x, cell.y) == -2 || getBoardEl(cell.x, cell.y) == -1 || getBoardEl(cell.x, cell.y) == -3);
                cell.x++;
                cell.y++;
                qDebug() << "Attack: " << cell.x << " " << cell.y;
                return cell;
            }
         else
         {

            for (int i = 0; i < n - 1; i++)
            {
                for (int j = 0; j < n - 1; j++)
                    if (getBoardEl(i, j) == -1)
                    {
                        I = i; J = j;
                        goto stop;
                    }
            }

            stop:
            if (I != -1)
            {
                if (getBoardEl(I, J + 1) == -1 || getBoardEl(I, J - 1) == -1)
                {
                    while (getBoardEl(I, J + k) == -1)k++;
                    if (J + k < n - 2 && getBoardEl(I, J + k) !=-2)
                    {
                        cell.x = I + 1;
                        cell.y = J + k + 1;
                        qDebug() << "Attack: " << cell.x << " " << cell.y;
                        return cell;
                    }

                    k = 1;
                    while (getBoardEl(I, J - k) == -1)k++;
                    if (J - k >= 0 && getBoardEl(I, J - k) != -2)
                    {
                        cell.x = I + 1;
                        cell.y = J - k + 1;
                        qDebug() << "Attack: " << cell.x << " " << cell.y;
                        return cell;
                    }
                }
                else if (getBoardEl(I + 1, J) == -1 || getBoardEl(I - 1, J) == -1)
                {
                    k = 1;
                    while (getBoardEl(I + k, J) == -1)k++;
                    if (I + k < n - 2 && getBoardEl(I + k, J) !=-2)
                    {
                        cell.x = I + k + 1;
                        cell.y = J + 1;
                        qDebug() << "Attack: " << cell.x << " " << cell.y;
                        return cell;
                    }

                    k = 1;
                    while (getBoardEl(I - k, J) == -1)k++;
                    if (I - k >= 0 && getBoardEl(I - k, J) != -2)
                    {
                        cell.x = I - k + 1;
                        cell.y = J + 1;
                        qDebug() << "Attack: " << cell.x << " " << cell.y;
                        return cell;
                    }
                }
                    k = 1;
                    while (getBoardEl(I + k, J) == -1)k++;
                    if (I + k < n - 2 && getBoardEl(I + k, J) != -2)
                    {
                        cell.x = I + k + 1;
                        cell.y = J + 1;
                        qDebug() << "Attack: " << cell.x << " " << cell.y;
                        return cell;
                    }

                    k = 1;
                    while (getBoardEl(I - k, J) == -1)k++;
                    if (I - k >= 0 && getBoardEl(I - k, J) != -2)
                    {
                        cell.x = I - k + 1;
                        cell.y = J + 1;
                        qDebug() << "Attack: " << cell.x << " " << cell.y;
                        return cell;
                    }
                    k = 1;
                    while (getBoardEl(I, J + k) == -1)k++;
                    if (J + k < n - 2 && getBoardEl(I, J + k) != -2)
                    {
                        cell.x = I + 1;
                        cell.y = J + k + 1;
                        qDebug() << "Attack: " << cell.x << " " << cell.y;
                        return cell;
                    }
                    k = 1;
                    while (getBoardEl(I, J - k) == -1)k++;
                    if (J - k >= 0 && getBoardEl(I, J - k) != -2)
                    {
                        cell.x = I + 1;
                        cell.y = J - k + 1;
                        qDebug() << "Attack: " << cell.x << " " << cell.y;
                        return cell;
                    }
           // }
            }
            else
            {
                num++;
                if ((level == medium && num%5==0) || (level == hard && num%3==0 ) || level==very_hard)
                {

                    for (int i = 0; i < n - 1; i++)
                    {
                        for (int j = 0; j < n - 1; j++)
                            if (board[i][j] > 0)
                            {
                                I=i; J=j;
                                goto stop2;
                            }
                    }

                    stop2:

                    cell.x=I; cell.y=J;
                    return cell;
                }
                else
                    if ((level == medium && num%5!=0) || level==easy || (level == hard && num%3!=0 ))
                {
                     do{
                        cell.x = qrand() % (n - 2);
                        cell.y = qrand() % (n - 2);
                     }while (getBoardEl(cell.x, cell.y) == -2 || getBoardEl(cell.x, cell.y) == -1 || getBoardEl(cell.x, cell.y) == -3);
                    cell.x++;
                    cell.y++;
                    qDebug() << "Attack: " << cell.x << " " << cell.y;
                    return cell;
                }
            }
        }
    }
    */
    void Player::checkAttack(Cell cell)
    {
        int boardElem = board[cell.x][cell.y];

        if (boardElem < 0)
        {
            //emit nextTurn();
            return;
        }

        if (boardElem == 0)
        {
            Boner(cell.x, cell.y);
            return;
        }

        Ship &ship = flot[boardElem - 1];
        ship.setHit();
        sum++;

        if (ship.getHit() < ship.getDesks())
        {
            Hit(cell.x, cell.y);
        }
        if (ship.getHit() == ship.getDesks())
        {
            Kill(cell.x, cell.y);
        }
        //сигнал завершения игры
        if (sum == 20) emit endGame();
        return;
    }


Player::~Player()
{
    delete ship;
}


