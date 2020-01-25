#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
#if defined Q_OS_WIN
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
//    paths.append("imageformats");
//    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
