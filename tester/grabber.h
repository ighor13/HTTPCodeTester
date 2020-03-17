#ifndef GRABBER_H
#define GRABBER_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class Grabber;
}

class Grabber : public QDialog
{
    Q_OBJECT

public:
    explicit Grabber(QWidget *parent = nullptr);
    ~Grabber();
    QStringList result;
private slots:
    void on_scanButton_clicked();
    void on_addButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::Grabber *ui;
};

#endif // GRABBER_H
