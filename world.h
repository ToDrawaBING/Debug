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
    World(){}
    ~World(){}

    void initWorld();

    void show(QPainter * painter);


    void erasObj(int x, int y);
private:
    vector<RPGobj *> _objs;



};

#endif // WORLD_H
