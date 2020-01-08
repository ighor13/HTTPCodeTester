/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_From_File;
    QAction *actionSave_To_File;
    QAction *actionAbout;
    QAction *actionLoad_From_Clipboard;
    QAction *actionCopy_To_Clipboard;
    QAction *actionClea_r_All;
    QAction *actionE_xit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QMenuBar *menubar;
    QMenu *menuPush_me_too;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1156, 522);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        actionLoad_From_File = new QAction(MainWindow);
        actionLoad_From_File->setObjectName(QString::fromUtf8("actionLoad_From_File"));
        actionSave_To_File = new QAction(MainWindow);
        actionSave_To_File->setObjectName(QString::fromUtf8("actionSave_To_File"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionLoad_From_Clipboard = new QAction(MainWindow);
        actionLoad_From_Clipboard->setObjectName(QString::fromUtf8("actionLoad_From_Clipboard"));
        actionCopy_To_Clipboard = new QAction(MainWindow);
        actionCopy_To_Clipboard->setObjectName(QString::fromUtf8("actionCopy_To_Clipboard"));
        actionClea_r_All = new QAction(MainWindow);
        actionClea_r_All->setObjectName(QString::fromUtf8("actionClea_r_All"));
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(frame);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        font.setPointSize(8);
        tableWidget->setFont(font);
        tableWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        horizontalLayout->addWidget(progressBar);

        startButton = new QPushButton(frame);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/play.ico"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon);

        horizontalLayout->addWidget(startButton);

        pauseButton = new QPushButton(frame);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pause.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon1);

        horizontalLayout->addWidget(pauseButton);

        stopButton = new QPushButton(frame);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/stop.ico"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon2);

        horizontalLayout->addWidget(stopButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1156, 21));
        menuPush_me_too = new QMenu(menubar);
        menuPush_me_too->setObjectName(QString::fromUtf8("menuPush_me_too"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuPush_me_too->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuPush_me_too->addAction(actionClea_r_All);
        menuPush_me_too->addSeparator();
        menuPush_me_too->addAction(actionLoad_From_File);
        menuPush_me_too->addAction(actionSave_To_File);
        menuPush_me_too->addSeparator();
        menuPush_me_too->addAction(actionLoad_From_Clipboard);
        menuPush_me_too->addAction(actionCopy_To_Clipboard);
        menuPush_me_too->addSeparator();
        menuPush_me_too->addAction(actionE_xit);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HTTP Code Tester", nullptr));
        actionLoad_From_File->setText(QApplication::translate("MainWindow", "&Load From File...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionLoad_From_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_To_File->setText(QApplication::translate("MainWindow", "&Save To File...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_To_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionAbout->setText(QApplication::translate("MainWindow", "&About...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionLoad_From_Clipboard->setText(QApplication::translate("MainWindow", "Load &From Clipboard!", nullptr));
#ifndef QT_NO_SHORTCUT
        actionLoad_From_Clipboard->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionCopy_To_Clipboard->setText(QApplication::translate("MainWindow", "&Copy To Clipboard!", nullptr));
#ifndef QT_NO_SHORTCUT
        actionCopy_To_Clipboard->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionClea_r_All->setText(QApplication::translate("MainWindow", "Clea&r All", nullptr));
#ifndef QT_NO_SHORTCUT
        actionClea_r_All->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_NO_SHORTCUT
        actionE_xit->setText(QApplication::translate("MainWindow", "E&xit!", nullptr));
#ifndef QT_NO_SHORTCUT
        actionE_xit->setShortcut(QApplication::translate("MainWindow", "Alt+X", nullptr));
#endif // QT_NO_SHORTCUT
        startButton->setText(QApplication::translate("MainWindow", "START", nullptr));
        pauseButton->setText(QApplication::translate("MainWindow", "PAUSE", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "STOP", nullptr));
        menuPush_me_too->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
