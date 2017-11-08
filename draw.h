#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPoint>
#include <QtGui>

class draw : public QWidget
{
    Q_OBJECT
private:
    bool point;
    QPoint q;
    std::vector<QPoint> points;
    struct list{/*chci vektor ukazatelu na jednotlivy polygony*/};

public:
    explicit draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void clear();
    std::vector<QPoint> getPoints(){return points;}
    QPoint getQ(){return q;}
    void setStatus(bool status) {point = status;}
    void fillPolygon(/*viz cpp soubor*/);

signals:

public slots:
};

#endif // DRAW_H
