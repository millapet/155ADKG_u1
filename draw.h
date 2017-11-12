#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPoint>
#include <QtGui>
#include<QString>
#include<fstream>
#include<vector>

class draw : public QWidget
{
    Q_OBJECT
private:
    QPoint q;
    std::vector<std::vector<QPoint>> poly_list; //polygon list with all the loaded values
    std::vector<QPoint> points;
    std::vector<int> result_polygons; //polygons to be colored

public:
    explicit draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void clear();
    std::vector<QPoint> getPoints(){return points;}
    std::vector<std::vector<QPoint>> getList(){return poly_list;}
    QPoint getQ(){return q;}
    void loadData (const char* path, std::ifstream &file, QString &status);
    void setResultPolygons(std::vector<int> res){result_polygons = res;}


signals:

public slots:
};

#endif // DRAW_H
