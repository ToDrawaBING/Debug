#include "enemy.h"
#include <utility.h>

const QSize Enemy::_picsize(25,25);
int Enemy::_blood=100;

Enemy::Enemy(WayPoint *start, MainWindow *game, const QPixmap &image)
    :QObject(0)
{
    _image=image;
    _thegame=game;
    _pos=start->pos();
    _destination=start->nextWayPoint();
    _canmove=false;
    _speed=2.0;
    _currentblood=_blood;
}

void Enemy::drawe(QPainter *painter) const{
    if(!_canmove){
        return;
    }
    static const int bloodbandunhurt=100;

    painter->save();
    QPoint new_pos(_pos.x()-_picsize.width(),_pos.y()-_picsize.height());
    painter->drawPixmap(new_pos,_image);
    QPoint bloodbandpoint=new_pos+QPoint(-12,-20);
    QRect bloodband(bloodbandpoint,QSize(bloodbandunhurt,5));
    painter->drawRect(bloodband);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);

    QRect bloodbandhurt(bloodbandpoint,QSize((double)_currentblood/bloodbandunhurt*bloodbandunhurt,5));
    painter->drawRect(bloodbandhurt);

    painter->restore();
}

void Enemy::move(){
    if(!_canmove){
        return;
    }
    else {
    if(collision(_pos,1,_destination->pos(),1)){
        if(_destination->nextWayPoint()){
            _pos=_destination->pos();
            _destination=_destination->nextWayPoint();
            return;
        }
        else {
            _thegame->losehp(_damage);
            _thegame->removeEnemy(this);
            return;
        }
      }
    }
    qreal movementSpeed=_speed;
    QPoint next=_destination->pos();
    QVector2D normalized(next-_pos);
    normalized.normalize();
    _pos=_pos+normalized.toPoint()*movementSpeed;
}

bool Enemy::doActivate(){
    _canmove=true;
}

QPoint Enemy::getPos(){
    return _pos;
}

void Enemy::getHurt(int dmg){
    _currentblood-=dmg;
    this->_speed=1.0;
    if(_currentblood%20==0)
        this->_speed=2.0;
    if(_currentblood<=0){
        _thegame->getMoney(200);
        getRemoved();
    }
}
void Enemy::out(Tower *tower){
   attackingtowerlist.removeOne(tower);
}


void Enemy::getAttacked(Tower* tower){
    attackingtowerlist.push_back(tower);
}


void Enemy::getRemoved()
{
    if (attackingtowerlist.empty())
        return;

    foreach (Tower *attacker, attackingtowerlist)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    _thegame->removeEnemy(this);
}
