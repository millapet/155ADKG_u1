#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"

#include <QFileDialog>
//#include <QDesktopServices>
#include <fstream>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked() //when you click "clear"
{
    ui->Canvas->setStatus(false);
    ui->Canvas->clear();
}

void Widget::on_pushButton_3_clicked() //when you click "analyze"
{
    std::vector<int> result;
    QPoint q = ui->Canvas->getQ();

    std::vector<std::vector<QPoint>> poly_list;
    poly_list = ui->Canvas->getList();

    if(ui->comboBox->currentIndex() == 0)
        result = algorithms::iterateWindingPos(q, poly_list);
    else
        result = algorithms::iterateRayPos(q, poly_list);

    QString stringresult;
    for(int i=0;i<result.size();i++){
        stringresult += " "+result[i]; //TODO this may not work, do something better when testing is available
    }
    ui->label_2->setText(stringresult);

}

void Widget::on_pushButton_4_clicked() //when you click "set point" - will delete
{
    ui->Canvas->setStatus(true);
}

void Widget::on_pushButton_clicked() //when you click "load"
{
    double load_date[999];
    int j=0;

    QString fileident=QFileDialog::getOpenFileName(    //read *.txt file from disk C
             this,
             tr("seznam polygonu"),
             "C:\\",
             "Text File (*.txt)"); //podle zadani cvc ani nechce //mkay

    const char* pathident = fileident.toLatin1().data();

    std::ifstream fident;

    fident.open(pathident);

    while(!fident.eof()){
      j=j+1;
    fident>>load_date[j];
    } 
    fident.close();
    fident.clear();


    int poc=j/3; //number of points

    //arayes for partes of points
    int c_p_b[poc];
    double y_p_b[poc];
    double x_p_b[poc];

    int k;
    int q;
    int t;
    int i;

    for(k=1; k<=poc; k++){
    for(i=1; i<=3*k; i=i+3){
       c_p_b[k] = load_date[i];
    }
    for(q=2; q<=3*k; q=q+3){
        y_p_b[k] = load_date[q];
    }
    for(t=3; t<=3*k; t=t+3){
        x_p_b[k] = load_date[t];
    }
    }



    std::vector<std::vector<QPoint>> pols;
    std::vector<QPoint> pol;

   // put in the first vector pol first point
    QPoint inp_p (x_p_b[1], y_p_b[1]);
    pol.push_back(inp_p);

    int p=2;

    // loop all input vector pol till the end line all points execpt first one
    while(p != poc-1)  //because 1 point we've allready used
    {
        // where number of point is 1, load to vector
        if(c_p_b[p] != 1)
        {
             QPoint inp_p (x_p_b[p], y_p_b[p]);

            // compose pol
            pol.push_back(inp_p);
         // next point
            p ++;
        }
        else
        {
            // if name of the next point is 1, that mean that we have a new polygon
            pols.push_back(pol);
            pol.clear();

            // first position of a new polygon
            QPoint inp_p (x_p_b[p], y_p_b[p]);
            pol.push_back(inp_p);

             p++;
        }
    }
}
