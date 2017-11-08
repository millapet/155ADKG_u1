#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"

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

void Widget::on_pushButton_2_clicked()
{
    ui->Canvas->setStatus(false);
    ui->Canvas->clear();
}

void Widget::on_pushButton_3_clicked()
{
    int result;
    QPoint q = ui->Canvas->getQ();

    std::vector<QPoint> points;
    points = ui->Canvas->getPoints();

    if(ui->comboBox->currentIndex() == 0)
        result = algorithms::getWindingPos(q, points);
    else
        result = algorithms::getRayPos(q, points);

    ui->label_2->setText(QString::number(result));

}

void Widget::on_pushButton_4_clicked()
{
    ui->Canvas->setStatus(true);
}
