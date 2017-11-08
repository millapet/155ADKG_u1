#include "draw.h"


draw::draw(QWidget *parent) : QWidget(parent)
{
    point = false;
}


void draw::mousePressEvent(QMouseEvent *e)
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
    //tohle budu muset udelat pro kazdy polygon ve vektoru polygonu
    //pokud dojdu k vektoru ktery je ten ve kterem je bod, tak ho vybarvim
    //as seen below
    QPolygon polygon;

    for (int i=0;i < points.size(); i++)
    {
        polygon.append(points[i]);
    }
    painter.drawEllipse(q.x() - 5 ,q.y()-5, 10, 10);
    QBrush brush(Qt::red,Qt::Dense1Pattern);
    painter.setBrush(brush);
    painter.drawPolygon(polygon,Qt::WindingFill); //juchu, kreslim barevny polygony
    //pokud je true (nebo spis cislo polygonu) tak vybarvit urcity polygon?
    painter.end();
}

void draw::fillPolygon(/*tady bude neco podle ceho poznam kterej polygon to je*/){

}

void draw::clear()
{
    points.clear();
    repaint();
}
