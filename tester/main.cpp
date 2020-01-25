#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
//    paths.append("imageformats");
//    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
