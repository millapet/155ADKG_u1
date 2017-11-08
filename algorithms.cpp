#include "algorithms.h"

algorithms::algorithms()
{

}

int algorithms::getPosition(QPoint &q,QPoint &a, QPoint &b)
{
    double eps = 1.0e-6;
    double ux = b.x() - a.x();
    double uy = b.y() - a.y();
    double vx = q.x() - a.x();
    double vy = q.y() - a.y();

    double det = (ux * vy - uy * vx);
    if(det>eps)
        return 1;

    if(det<-eps)
        return 0;

    return -1;
}

double algorithms::getAngle(QPoint &p1,QPoint &p2,QPoint &p3, QPoint &p4)
{
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();
    double vx = p4.x() - p3.x();
    double vy = p4.y() - p3.y();

    double s = ux * vx + uy * vy;
    double normU = sqrt(ux * ux + uy * uy);
    double normV = sqrt(vx * vx + vy * vy);

    double test =  (acos(s/(normU * normV)))*(180/M_PI);
    return fabs(acos(s/(normU * normV)))*(180/M_PI);
}


int algorithms::getWindingPos(QPoint &q, std::vector<QPoint> pol)
{
    double om=0.0;
    double eps = 1.0e-6;

    //Add first point as the last one
    pol.push_back(pol[0]);

    //Process all polygon segments
    for (int i=0;i<pol.size()-1;i++)
    {
        //Get angle
        double om_l=getAngle(pol[i], q, pol[i+1], q);

        //Get position
        int t = getPosition(q, pol[i], pol[i+1]);

        //Point q in the left halfplane
        if(t > 0)
            om += om_l;

        //Point in the right halfplane
        else
            om -= om_l;
    }

    //Difference from 2 * PI
    double omt = fabs(om)-360.0;

    //POint q inside P
    if (fabs(omt)<eps)
        return 1;

    //Point q outside P
    else
        return 0;

}

int algorithms::getRayPos(QPoint &q, std::vector<QPoint> pol){

    int k=0;

    //Add first point as the last one
    pol.push_back(pol[0]);

    //Process all polygon segments
    for (int i=0;i<pol.size()-1;i++)
    {
        //Get reduced points of the line segment
        double xi = pol[i].x()-q.x();
        double yi = pol[i].y()-q.y();
        double xii= pol[i+1].x()-q.x();
        double yii= pol[i+1].y()-q.y();

        //A suitable line segment
        if((yi<=0)&&(yii>0)||(yii<=0)&&(yi>0))
        {
            //Point inn the right halfplane
            double xn = (xii*yi - xi*yii)/(yii - yi);
            if (xn > 0)
                k++;
        }
    }

    int z = k % 2;

    if (z==0)
        return 0;
    else
        return 1;
}









