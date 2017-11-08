#include "draw.h"


draw::draw(QWidget *parent) : QWidget(parent)
{
    point = false;
}


void draw::mousePressEvent(QMouseEvent *e) //tohle nebude ve finalni verzi
{
    if (point)
    {
        q.setX(e->pos().x());
        q.setY(e->pos().y());
    }

    else
    {
        QPoint p(e->pos().x(), e->pos().y());
        points.push_back(p);
    }

    repaint();


}

void draw::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.begin(this);
    for (int j=0; j<poly_list.size();j++)
    { //iterate over all the polygons
        QPolygon polygon;
        for (int i=0;i < points.size(); i++) //iterate over each point in polygon
        {
            polygon.append(points[i]);
        }
        if(/*pokud je to ten nakliklej polygon*/j==2) //test if this is the clicked polygon - if true, fill in
        {
            QPainterPath path;
            path.addPolygon(polygon);
            QBrush brush(Qt::red,Qt::Dense1Pattern);
            painter.fillPath(path,brush);
        }
        else
        {
            painter.drawPolygon(polygon); //else just draw the outlines
        }
    }

    painter.drawEllipse(q.x() - 5 ,q.y()-5, 10, 10);
    painter.end();
}

void draw::fillPolygon(/*tady bude neco podle ceho poznam kterej polygon to je*/){

}

void draw::clear()
{
    points.clear();
    repaint();
}
