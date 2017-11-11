#include "draw.h"


draw::draw(QWidget *parent) : QWidget(parent)
{
p_flag = false;
}


void draw::mousePressEvent(QMouseEvent *e)
{
    q.setX(e->pos().x());
    q.setY(e->pos().y());
    repaint();


}

void draw::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    //painter.begin(this);
    if(p_flag){
        for (int j=0; j<poly_list.size();j++)
           { //iterate over all the polygons
               QPolygon polygon;
               for (int i=0;i < points.size(); i++) //iterate over each point in polygon
               {
                   polygon.append(points[i]);
               }
               painter.drawPolygon(polygon); //draw the outlines
           }
        p_flag=false; //set back to point drawing
    }
    else{
        painter.drawEllipse(q.x() - 5 ,q.y()-5, 10, 10);
    }
    //paintEvent(e);
    //painter.end();
}

void draw::drawPolygons(){
    p_flag = true;
    repaint();
}

void draw::clear()
{
    //points.clear();
    poly_list.clear();
    repaint();
}

void draw::loadData (const char* path, std::ifstream &file, QString &status){
    try{
        file.open(path);
        if(!file.is_open()){
            status = "Error: Failed to open polygon file.";
            file.close();
        }

        //how many polygons?
        int poly_count;
        file >> poly_count;
        if (poly_count==0){
            status = "Error: No polygons found.";
            return;
        }
        //initialize the right number of vectors in the main vector
        std::vector<std::vector<QPoint> > tmp(poly_count, std::vector<QPoint>(0));
        //swap the temporary vector with the class vector
        std::swap(poly_list, tmp);

        int p = 0; //number of polygon being processed

        //temporary vector for storing polygon's x coordinates
        std::vector<double> tmp_x;

        while (file.good()){
            //number of points in one polygon
            int pt_count;
            file >> pt_count;
            if (pt_count<3){
                status = "Error: Cannot enter a polygon with less than 3 points.";
                return;
            }
            //if the capacity of the vector is less than what we need, reserve more space
            if(tmp_x.capacity()<pt_count){
                tmp_x.reserve(pt_count);
            }
            //reserve space in the final vector
            poly_list[p].reserve(pt_count);

            //load x coordinates of a polygon
            for(int i=0; i<pt_count;i++){
                file>>tmp_x[i];
            }

            //load each y coordinate and store the QPoint
            double tmp_y;
            for(int i=0; i<pt_count; i++){
                file>>tmp_y;
                poly_list[p].push_back(QPoint(tmp_x[i],tmp_y));
            }
            p++;
        }
        file.close();
        if(!poly_list.empty()){
        status = "Polygon loaded successfully.";
        return;
        }
        status = "Oops! Something went wrong.";
    }
    catch(...){
    status = "Error: Unknown Exception.";
    }
}
