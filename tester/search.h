#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();
    QStringList data;

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::Search *ui;

protected:
    void Search::showEvent(QShowEvent *);

};
#endif // SEARCH_H
