#ifndef GRABBER_H
#define GRABBER_H

#include <QDialog>
#include <QDebug>
#include <QGuiApplication>
#include <QThread>
#include <QMutex>
#include <QListWidget>
#include <QNetworkReply>
#include <QTextCodec>
#include <QMap>
#include <qgumbodocument.h>
#include <qgumbonode.h>

#define HTTP_MAX_THREADS 3

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
    void updateurl(const QUrl);
    void on_addSelectdButton_clicked();

private:
    Ui::Grabber *ui;
    QMutex mutex;
    QUrl startfrom;
    QMap<QString,bool> done;

};



class GThread : public QThread
{
    Q_OBJECT

public:
    GThread(QListWidget *givenmodel, QMutex& givenmutex, const QUrl url, QObject *parent);
    ~GThread();
    static int thrcount;

protected:
    QListWidget *model;
    QMutex &mutex;
    QUrl url;
    enum States {none, ready, skip} state;
    void run();
private slots:
    void httpRequestFinished(QNetworkReply*);
    //void httpRequestError(QNetworkReply::NetworkError);
signals:
    void status(QString,int);

};
#endif // GRABBER_H
