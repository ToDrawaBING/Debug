#ifndef UTILITY_H
#define UTILITY_H
#include <qpoint.h>
#include <math.h>

inline bool collision(QPoint point1,int r1,QPoint point2,int r2){
    const int xdis=point1.x()-point2.x();
    const int ydis=point1.y()-point2.y();
    const double distance=sqrt(fabs(xdis*xdis+ydis*ydis));
    if(distance<=r1+r2)
        return true;
    else
        return false;
}

#endif // UTILITY_H
