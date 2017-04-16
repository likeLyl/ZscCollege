/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Thu Mar 23 22:55:18 2017
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLineEdit *line_IP;
    QLineEdit *line_PORT;
    QLineEdit *line_GET;
    QLineEdit *line_FILENAME;
    QTextBrowser *textBrowser;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(806, 655);
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    pushButton = new QPushButton(centralWidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(530, 120, 92, 27));
    line_IP = new QLineEdit(centralWidget);
    line_IP->setObjectName(QString::fromUtf8("line_IP"));
    line_IP->setGeometry(QRect(40, 50, 113, 27));
    line_PORT = new QLineEdit(centralWidget);
    line_PORT->setObjectName(QString::fromUtf8("line_PORT"));
    line_PORT->setGeometry(QRect(190, 50, 113, 27));
    line_GET = new QLineEdit(centralWidget);
    line_GET->setObjectName(QString::fromUtf8("line_GET"));
    line_GET->setGeometry(QRect(350, 50, 113, 27));
    line_FILENAME = new QLineEdit(centralWidget);
    line_FILENAME->setObjectName(QString::fromUtf8("line_FILENAME"));
    line_FILENAME->setGeometry(QRect(520, 50, 113, 27));
    textBrowser = new QTextBrowser(centralWidget);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setGeometry(QRect(40, 170, 571, 401));
    label = new QLabel(centralWidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(40, 30, 59, 17));
    label_2 = new QLabel(centralWidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(190, 30, 59, 17));
    label_3 = new QLabel(centralWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(350, 30, 91, 17));
    label_4 = new QLabel(centralWidget);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(520, 30, 71, 17));
    MainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 806, 24));
    MainWindow->setMenuBar(menuBar);
    mainToolBar = new QToolBar(MainWindow);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MainWindow->setStatusBar(statusBar);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("MainWindow", "IP", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("MainWindow", "PORT", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("MainWindow", "GET or PUSH", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("MainWindow", "FILENAME", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
