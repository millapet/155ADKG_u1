#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"

#include <QFileDialog>
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

void Widget::on_pushButton_clear_clicked() //when you click "clear"
{
    ui->Canvas->clear();
}

void Widget::on_pushButton_analyze_clicked() //when you click "analyze"
{
    try{
    std::vector<int> result;
    QPoint q = ui->Canvas->getQ();

    std::vector<std::vector<QPoint>> poly_list;
    poly_list = ui->Canvas->getList();

    //check which algorithm is selected and find point
    if(ui->comboBox->currentIndex() == 0)
        result = algorithms::iterateWindingPos(q, poly_list);
    else
        result = algorithms::iterateRayPos(q, poly_list);
    ui->Canvas->setResultPolygons(result);
    ui->Canvas->repaint();

    //report status in label
    QString status = "Point lies in "+QString::number(result.size())+" polygon(s)";
    ui->analyze_label->setText(status);
    }
    catch(...){
        ui->analyze_label->setText("Error: Unknown exception appeared.");
    }

}

void Widget::on_pushButton_load_clicked() //when you click "load"
{
    try{
    QString chosen_file=QFileDialog::getOpenFileName(    //select file
                 this,
                 tr("Load polygons"),
                 "C:\\",
                 "Text File (*.txt)");

        const char* path = chosen_file.toLatin1().data();
        std::ifstream file;
        QString status;

        ui->Canvas->loadData(path, file, status); //call file loading function
        ui->status_label->setText(status); //report status in label
        ui->Canvas->repaint(); //draw the newly loaded polygons
        }
    catch(...){
        ui->status_label->setText("Error: Unknown exception appeared.");
    }
}

