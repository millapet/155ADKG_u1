#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <vector>

#include <QPoint>


class algorithms
{
public:
    algorithms();
    static int getPosition(QPoint &p,QPoint &a,QPoint &b);
    static double getAngle(QPoint &,QPoint &,QPoint &, QPoint &); //calculates angle between points
    static std::vector<int> iterateWindingPos(QPoint &q, std::vector<std::vector<QPoint>> pol_list); //returns indexes of polygons containing q
    static std::vector<int> iterateRayPos(QPoint &q, std::vector<std::vector<QPoint>> pol_list); //returns indexes of polygons containing q

private:
    //std::vector<int> poly_index;
    static bool getWindingPos(QPoint &q, std::vector<QPoint> pol); //returns bool - whether the point is in a polygon or not
    static bool getRayPos(QPoint &q, std::vector<QPoint> pol); //returns bool - whether the point is in a polygon or not
};

#endif // ALGORITHMS_H
