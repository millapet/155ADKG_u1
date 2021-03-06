#include "algorithms.h"

algorithms::algorithms()
{

}

int algorithms::getPosition(QPoint &q,QPoint &a, QPoint &b)
{
    //double eps = 1.0e-6;
    double eps = 5;
    double ux = b.x() - a.x();
    double uy = b.y() - a.y();
    double vx = q.x() - a.x();
    double vy = q.y() - a.y();

    double det = (ux * vy - uy * vx);
    if(det<eps && det>-eps)
        {
                double wx = q.x() - b.x();
                double wy = q.y() - b.y();
                double dist_bq =sqrt(wx*wx+wy*wy);
                double dist_ab =sqrt(ux*ux+uy*uy);
                double dist_aq = std::sqrt(vx*vx+vy*vy);
                double sum_dist = dist_aq + dist_bq;
                //if sum of distance between AQ and BQ is equal to AB - bingo
                if((sum_dist-dist_ab)<=eps && (sum_dist-dist_ab)>=-eps)
                return 2;
            }
    else if(det>eps)
        return 1;

    else if(det<-eps)
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

    //double test =  (acos(s/(normU * normV)))*(180/M_PI);
    return fabs(acos(s/(normU * normV)))*(180/M_PI);
}


bool algorithms::getWindingPos(QPoint &q, std::vector<QPoint> pol)
{
    double om=0.0;
    double eps = 1.0e-6;

    //Add first point as the last one
    pol.push_back(pol[0]);

    //Process all polygon segments
    for (unsigned int i=0;i<pol.size()-1;i++)
    {
        //Get angle
        double om_l=getAngle(pol[i], q, pol[i+1], q);

        //Get position
        int t = getPosition(q, pol[i], pol[i+1]);

        //Point is on the line - we know it is in
        if(t==2)
            return 1;

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

bool algorithms::getRayPos(QPoint &q, std::vector<QPoint> pol){

    int k=0;

    //Add first point as the last one
    pol.push_back(pol[0]);

    //Process all polygon segments
    for (unsigned int i=0;i<pol.size()-1;i++)
    {
        //First test if the point is on the line
        if(getPosition(q, pol[i], pol[i+1])==2) return 1;

        //Get reduced points of the line segment
        double xi = pol[i].x()-q.x();
        double yi = pol[i].y()-q.y();
        double xii= pol[i+1].x()-q.x();
        double yii= pol[i+1].y()-q.y();

        //A suitable line segment
        if(((yi<=0)&&(yii>0))||((yii<=0)&&(yi>0)))
        {
            //Point in the right halfplane
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

std::vector<int> algorithms::iterateWindingPos(QPoint &q, std::vector<std::vector<QPoint>> pol_list){
    std::vector<int> res;
    for(unsigned int i=0;i<pol_list.size();i++){
        if(getWindingPos(q,pol_list[i])==1) res.push_back(i); //returns index of the first polygon that passes
    }
    return res;
}

std::vector<int> algorithms::iterateRayPos(QPoint &q, std::vector<std::vector<QPoint>> pol_list){
    std::vector<int> res;
    for(unsigned int i=0;i<pol_list.size();i++){
        if(getRayPos(q,pol_list[i])==1) res.push_back(i); //returns index of the first polygon that passes
    }
    return res;
}







