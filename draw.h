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
    std::vector<std::vector<QPoint>> poly_list;
    std::vector<QPoint> points;

public:
    explicit draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void clear();
    std::vector<QPoint> getPoints(){return points;}
    std::vector<std::vector<QPoint>> getList(){return poly_list;}
    QPoint getQ(){return q;}
    //void drawPolygons();
    void loadData (const char* path, std::ifstream &file, QString &status);
    //void placePoint(){p_flag = false;}

signals:

public slots:
};

#endif // DRAW_H
