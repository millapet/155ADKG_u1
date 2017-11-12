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

void Widget::on_pushButton_2_clicked() //when you click "clear"
{
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

    QString string_result;
    for(int i=0;i<result.size();i++){
        string_result += " "+QString::number(result[i]); //TODO this may not work, do something better when testing is available
    }
    ui->analyze_label->setText(string_result);

}

void Widget::on_pushButton_clicked() //when you click "load"
{
    QString chosen_file=QFileDialog::getOpenFileName(    //read *.txt file from disk C
                 this,
                 tr("seznam polygonu"),
                 "C:\\",
                 "Text File (*.txt)"); //podle zadani cvc ani nechce //mkay

        const char* path = chosen_file.toLatin1().data();
        std::ifstream file;
        QString status;

        ui->Canvas->loadData(path, file, status);
        ui->status_label->setText(status);
        ui->Canvas->repaint();
}

