#ifndef WAYPOINT_H
#define WAYPOINT_H
#include <qpoint.h>
#include <qpainter.h>

class WayPoint
{
public:
    WayPoint(QPoint pos);
    void SetNextWayPoint(WayPoint *nextpoint);
    WayPoint* nextWayPoint();
    QPoint pos();
private:
    QPoint m_pos;
    WayPoint* m_nextWayPoint;
};

#endif // WAYPOINT_H
