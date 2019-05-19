#include "tool.h"

Tool::Tool()
{

}

void Tool::erase(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl(":/music/cointool.mp3"));
    player->setVolume(30);
    player->play();

}
