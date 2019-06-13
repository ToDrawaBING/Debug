#ifndef ENEMY_H
#define ENEMY_H
#include "QPainter"
#include "QList"
#include <waypoint.h>
#include <mainwindow.h>

class MainWindow;
class Tower;

class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *start,MainWindow *game,const QPixmap &image=QPixmap(":/images/mushroom.png"));
    ~Enemy(){}
    void drawe(QPainter *painter) const;
    void move();

    void getAttacked(Tower * tower);
    void getHurt(int dmg);
    void getRemoved();
    void out(Tower *tower);
    QPoint getPos();
private slots:
    bool doActivate();
protected:
    double _speed;
    static int _blood;
    static const QSize _picsize;
    QPixmap _image;
    WayPoint *_destination;
    MainWindow *_thegame;
    QPoint _pos;
    bool _canmove;
    //攻击塔
    QList<Tower *> attackingtowerlist;
    int _currentblood;
    int _damage=1;

};

#endif // ENEMY_H
