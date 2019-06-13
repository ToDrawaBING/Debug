#include "enemy2.h"
#include <enemy.h>

Enemy2::Enemy2(WayPoint *start,MainWindow *game,const QPixmap &image)
    :Enemy(start,game,image)
{
    _speed = 2.5;
}
