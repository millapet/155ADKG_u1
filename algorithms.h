#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <vector>

#include <QPointF>


class algorithms
{
public:
    algorithms();
    static int getPosition(QPointF &p,QPointF &a,QPointF &b);
    static double getAngle(QPointF &,QPointF &,QPointF &, QPointF &); //calculates angle between points
    static std::vector<int> iterateWindingPos(QPointF &q, std::vector<std::vector<QPointF>> pol_list); //returns indexes of polygons containing q
    static std::vector<int> iterateRayPos(QPointF &q, std::vector<std::vector<QPointF>> pol_list); //returns indexes of polygons containing q

private:
    //std::vector<int> poly_index;
    static bool getWindingPos(QPointF &q, std::vector<QPointF> pol); //returns bool - whether the point is in a polygon or not
    static bool getRayPos(QPointF &q, std::vector<QPointF> pol); //returns bool - whether the point is in a polygon or not
};

#endif // ALGORITHMS_H
