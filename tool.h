#ifndef TOOL_H
#define TOOL_H
#include "rpgobj.h"
#include <QMediaPlayer>
using namespace std;

class Tool:public RPGobj
{
public:
    Tool();
    ~Tool(){}

    void erase();

};

#endif // TOOL_H
