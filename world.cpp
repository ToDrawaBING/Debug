#include "world.h"


void World::initWorld(){
    RPGobj *s1 = new RPGobj,*s2 = new RPGobj,*s3 = new RPGobj;
    s1->initObj("stone");
    s2->initObj("stone");
    s3->initObj("stone");

    s1->setPosX(20);
    s1->setPosY(15);

    s2->setPosX(35);
    s2->setPosY(17);

    s3->setPosX(14);
    s3->setPosX(10);

    RPGobj *f1 = new RPGobj,*f2 = new RPGobj;
    f1->initObj("flower");
    f2->initObj("flower");

    f1->setPosX(27);
    f1->setPosY(30);

    f2->setPosX(17);
    f2->setPosY(14);

    RPGobj *t1 = new Tool;
    t1->initObj("tool");
    t1->setPosX(18);
    t1->setPosY(22);

    this->_objs.push_back(s1);
    this->_objs.push_back(s2);
    this->_objs.push_back(s3);

    this->_objs.push_back(f1);
    this->_objs.push_back(f2);

    this->_objs.push_back(t1);

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl(":/music/BGM.mp3"));
    player->setVolume(30);
    player->play();

}

void World::show(QPainter *painter){
    int n = this->_objs.size();
    for (int i=0;i<n;i++){
        this->_objs[i]->show(painter);
    }
   // this->_player->show(painter);
}

void World::erasObj(int x, int y){
    vector<RPGobj*>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
       if (((*it)->getPosX() == x) && ((*it)->getPosY()==y) ){
            (*it)->onErase();
            this->_objs.erase(it);//删除world里的物体
            delete (*it);
            break;
        }
    }
}

