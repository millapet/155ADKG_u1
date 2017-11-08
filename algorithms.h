#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QPoint>
#include <vector>


class algorithms
{
public:
    algorithms();
    static int getPosition(QPoint &p,QPoint &a,QPoint &b);
    static double getAngle(QPoint &,QPoint &,QPoint &, QPoint &);
    static std::vector<int> iterateWindingPos(QPoint &q, std::vector<std::vector<QPoint>> pol_list); //returns indexes of polygons containing q
    static std::vector<int> iterateRayPos(QPoint &q, std::vector<std::vector<QPoint>> pol_list); //returns indexes of polygons containing q
    static bool getWindingPos(QPoint &q, std::vector<QPoint> pol); //returns bool
    static bool getRayPos(QPoint &q, std::vector<QPoint> pol); //returns bool

private:
    //std::vector<int> poly_index;
};

#endif // ALGORITHMS_H
