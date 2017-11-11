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
    painter.begin(this);
    if(p_flag){
        for (int j=0; j<poly_list.size();j++)
           { //iterate over all the polygons
               QPolygon polygon;
               for (int i=0;i < points.size(); i++) //iterate over each point in polygon
               {
                   polygon.append(points[i]*100);
               }
               painter.drawPolygon(polygon); //draw the outlines
           }
        painter.drawEllipse(q.x() - 5 ,q.y()-5, 100, 100);
        p_flag=false; //set back to point drawing
    }
    else{
        painter.drawEllipse(q.x() - 5 ,q.y()-5, 10, 10);
    }
    //paintEvent(e);
    painter.end();
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
        //make room for the right ammount of polygons
        poly_list.clear();
        poly_list.reserve(poly_count);

        int p = 0; //number of polygon being processed
        while (file.good()){
            //make sure we start with an empty vector
            points.clear();
            //number of points in one polygon
            int pt_count;
            file >> pt_count;
            if (pt_count<3){
                status = "Error: Cannot enter a polygon with less than 3 points.";
                return;
            }
            //make space for the right ammount of points
            points.reserve(pt_count);
            //add points - x first
            for (int i = 0; i<pt_count; i++){
                int tmp_x;
                file>>tmp_x;
                points[i].setX(tmp_x);
            }
            //now add y coordinates from the second row
            for(int i=0; i<pt_count; i++){
                int tmp_y;
                file>>tmp_y;
                points[i].setY(tmp_y);
            }
            //add the polygon points to the list
            poly_list[p] = points;
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
