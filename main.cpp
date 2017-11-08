
#include "widget.h"
#include <QApplication>
#include <vector>
#include "algorithms.h"

int main(int argc, char *argv[])
{
    //Create polygon
    std::vector<QPoint> pol;
    pol.push_back(QPoint(0,0));
    pol.push_back(QPoint(10,0));
    pol.push_back(QPoint(5,5));
    pol.push_back(QPoint(10,10));
    pol.push_back(QPoint(0,10));

    //Create tested point
    QPoint q(10,5);

    //Test point and polygon position
    int t0 = algorithms::getRayPos(q,pol);

    //Simple test: position
    QPoint p(5,-5);
    QPoint b(0,0);
    QPoint c(10,0);
    int t1 = algorithms::getPosition(p,b,c);

    //Simple test: angle
    QPoint p2(5,5);
    QPoint b2(10,10);
    QPoint c2(10,0);
    int t2 = algorithms::getAngle(b2,p2,c2,p2);

    // POKUS O RANDOM GENERATOR POLYGONU - FAILED
    int edges = rand()%100; //rand number of edges from 0 to 99
    QPoint start((rand()%1000)/10, (rand()%1000)/10); //random coordinates of values 0 to 99,9
    QPoint centre((rand()%1000)/10, (rand()%1000)/10);
    for(int i = 0;i<edges;i++){
        double omega = rand()%2*M_PI; //random angle from 0 to 2*pi
        double dist = rand()%1000; //random distance from 0 to 1000
    }
//tady je problem nejenom s tim ze je potreba aby na sebe navazovaly ty polygony
    //ale taky s tim ze ty body v kazdym polygonu potrebujes v urcitym poradi - omega se neda takhle generovat
    //to by slo asi vyresit tim, ze se kruh rozdeli na tolik dilu, kolik je pocet vrcholu polygonu a pak se generuje cislo
    //jenom v rozmezi 0 az tenhle uhel a pricita se k predchozimu uhlu?

    //ty navazujici polygony by sly mozna tak, ze vezmes random cislo bodu z predchoziho polygonu a ty das do novyho a prigenerujes k tomu dalsi body?
    //ale zase potrebujes aby se ty body negenerovaly do polygonu kterej uz existuje

    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
