#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPointF>
#include <QtGui>
#include<QString>
#include<fstream>
#include<vector>

class draw : public QWidget
{
    Q_OBJECT
private:
    QPointF q;
    std::vector<std::vector<QPointF>> poly_list; //polygon list with all the loaded values
    std::vector<QPointF> points;
    std::vector<int> result_polygons; //polygons to be colored

public:
    explicit draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void clear();
    std::vector<QPointF> getPoints(){return points;} //access to private points
    std::vector<std::vector<QPointF>> getList(){return poly_list;} //access to private polygon list
    QPointF getQ(){return q;} //access to private point
    void loadData (const char* path, std::ifstream &file, QString &status); //function to load polygon coordinates
    void setResultPolygons(std::vector<int> res){result_polygons = res;} //sets the private variable containing the indexes of polygons with a point in them


signals:

public slots:
};

#endif // DRAW_H
