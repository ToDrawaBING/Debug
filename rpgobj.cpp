#include "rpgobj.h"
#include <iostream>

//enum object {stone,tool,fire,flower,bridge}
void RPGobj::initObj(string type)
{
    //TODO 所支持的对象类型应定义为枚举


     if (type.compare("stone")==0||
             type.compare("fire")==0||
                          type.compare("flower")==0){
        this->_coverable = false;
        this->_eatable = false;
    }

    else{
      \
        cout<<"invalid ICON type."<<endl;
        return;
    }

    this->_icon = ICON::findICON(type);
    QImage all;

    all.load(":/images/test.png");
    this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE,
                                _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
}//贴图

void RPGobj::show(QPainter * pa){
    int gSize = ICON::GRID_SIZE;
    pa->drawImage(this->_pos_x*gSize,this->_pos_y*gSize,this->_pic);
}//绘制图片

void RPGobj::onErase(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl(":/music/cointool.mp3"));
    player->setVolume(30);
    player->play();
}//道具被吃掉，播放音乐
