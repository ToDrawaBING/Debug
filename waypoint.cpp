#include "waypoint.h"

WayPoint::WayPoint(QPoint pos)
    :m_pos(pos)
    ,m_nextWayPoint(NULL)
{}

WayPoint* WayPoint::nextWayPoint(){
    return m_nextWayPoint;
}

void WayPoint::SetNextWayPoint(WayPoint *nextpoint){
    m_nextWayPoint=nextpoint;
}

QPoint WayPoint::pos(){
    return m_pos;
}


