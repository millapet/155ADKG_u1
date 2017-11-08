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
    int i=0;
    int j=0;
    double n[250];
    double m[9999];

    QString fileident=QFileDialog::getOpenFileName(
             this,
             tr("seznam polygonu"),
             "C:\\",
             "Text File (*.txt);; Tex File (*.cvc)"); //podle zadani cvc ani nechce

    const char* pathident = fileident.toLatin1().data();

    std::ifstream fident;

    fident.open(pathident);

    while(!fident.eof()){
      j=j+1;
    fident>>n[j];
    }
    fident.close();
    fident.clear();




}
