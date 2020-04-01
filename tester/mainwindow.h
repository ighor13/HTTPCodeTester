#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QClipboard>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextCodec>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QTableWidget>
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <fstream>
#include <sstream>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <grabber.h>

#define HTTP_MAX_THREADS 3


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int addItems(QStringList list);

private slots:
    void on_actionAbout_triggered();
    void on_actionSave_To_File_triggered();
    void on_actionLoad_From_Clipboard_triggered();
    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();
    void on_actionLoad_From_File_triggered();
    void on_actionClea_r_All_triggered();
    void on_actionE_xit_triggered();
    void updateurl(const int);
    void on_actionCopy_To_Clipboard_triggered();
    void on_actionLoad_from_X_ML_triggered();
    void on_actionLoad_from_Sitemap_URL_triggered();

private:
    Ui::MainWindow *ui;
    QMutex mutex;
    bool stop;
    bool pause;
    QNetworkAccessManager xmlmanager;
    unsigned Load(QDomDocument&); // returns count of loaded strings
private slots:
    void gotXML(QNetworkReply* );

    void on_action_Grab_from_site_triggered();
};


class QWaitCursor
{
public:
    QWaitCursor(){QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));}
    ~QWaitCursor(){QGuiApplication::restoreOverrideCursor();}
};


class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(QTableWidget *givenmodel, QMutex& givenmutex, int givenid, QObject *parent);
    ~Thread();
    static int thrcount;

protected:
    QTableWidget *model;
    QMutex &mutex;
    int id;
    QTime timer;
    void run();
private slots:
    void httpRequestFinished(QNetworkReply*);
    //void httpRequestError(QNetworkReply::NetworkError);
signals:
    void status(QString,int);

};

#endif // MAINWINDOW_H
