#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
}

Search::~Search()
{
    delete ui;
}

void Search::showEvent(QShowEvent *event)
{
        ui->listWidget->clear();
        int row = ui->listWidget->count();
        QListWidgetItem *item;
        unsigned count=0;
        for( auto q : data )
        {
            count++;
            item=new QListWidgetItem(q);
            item->setFlags (item->flags () | Qt::ItemIsEditable);
            ui->listWidget->insertItem(row++,item);
        }
}
void Search::on_saveButton_clicked()
{
    data.clear();
    for(unsigned i=0;i<ui->listWidget->count();++i)
        data.push_back(ui->listWidget->item(i)->text());
    this->close();
}


void Search::on_cancelButton_clicked()
{
    this->close();
}

