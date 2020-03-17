#include "grabber.h"
#include "ui_grabber.h"

Grabber::Grabber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grabber)
{
    ui->setupUi(this);
}

Grabber::~Grabber()
{
    delete ui;
}


void Grabber::on_scanButton_clicked()
{
    ui->listWidget->addItem(ui->lineEdit->text()); //...doesn't work...
}

void Grabber::on_addButton_clicked()
{
    int c = ui->listWidget->count();
    for (int i = 0; i < c ; ++i)
    {

        QString s = QString::number(i);
        QModelIndex *model_index = new QModelIndex(ui->listWidget->model()->index(i,0) ); //0th column since we have one cloumn in listwidget
        QString q= model_index->data(Qt::DisplayRole).toString();
        result.push_back(q);
//        qDebug()<<q;

    }
    this->close();
}

void Grabber::on_cancelButton_clicked()
{
    this->close();
}
