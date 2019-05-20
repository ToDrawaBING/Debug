#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <QPainter>
#include "rpgobj.h"
#include "tool.h"
#include <string>
#include "icon.h"
#include <QMediaPlayer>

using namespace std;

class World
{
public:
    World(){}//后期加上士兵初始化
    ~World(){}

    void initWorld();

    void show(QPainter * painter);
    //显示游戏世界所有对象,不确定有无用

    //玩家移动？

    void erasObj(int x, int y);
private:
    vector<RPGobj *> _objs;
    //加上士兵和敌人的指针


};

#endif // WORLD_H
