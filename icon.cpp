#include "icon.h"
#include<iostream>
int ICON::GRID_SIZE = 32;


pair<string,ICON> pairArray[] =
{
   // make_pair()玩家
    make_pair("flower",ICON("flower",5,4,1,1)),//装饰物2
    //可通过的桥
    make_pair("stone",ICON("stone",4,9, 1, 1)),
    make_pair("tool",ICON("tool",2,0, 1, 1))
};//进行贴图的定位

map<string,ICON> ICON::GAME_ICON_SET(pairArray,pairArray+sizeof(pairArray)/
                                     sizeof(pairArray[0]));//这句话我没懂


ICON::ICON(string name, int x, int y, int w, int h){
    this->typeName = name;
    this->srcX = x;
    this->srcY = y;
    this->width = w;
    this->height = h;
}

ICON ICON::findICON(string type){
    map<string,ICON>::iterator kv;//指针
    kv = ICON::GAME_ICON_SET.find(type);
    if (kv==ICON::GAME_ICON_SET.end()){

       cout<<"Error: cannot find ICON"<<endl;
       return ICON();
    }
    else{
        return kv->second;
    }
}
