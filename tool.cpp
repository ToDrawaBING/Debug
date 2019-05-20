#include "tool.h"
#include <QMediaPlayer>

void Tool::onErase(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl(":/music/cointool.mp3"));
    player->setVolume(30);
    player->play();
}
