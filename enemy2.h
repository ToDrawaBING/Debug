#ifndef ENEMY2_H
#define ENEMY2_H
#include <enemy.h>
class MainWindow;

class Enemy2:public Enemy
{
public:
    Enemy2(WayPoint *start,MainWindow *game,const QPixmap &image=QPixmap(":/images/mushroom2.png"));
    ~Enemy2(){}
private:
    int _damage=1;
};

#endif // ENEMY2_H
