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
    static int getWindingPos(QPoint &q, std::vector<QPoint> pol);
    static int getRayPos(QPoint &q, std::vector<QPoint> pol);

};

#endif // ALGORITHMS_H
