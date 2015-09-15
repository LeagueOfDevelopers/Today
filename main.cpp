#include <QDesktopWidget>
#include <QApplication>
#include <ctime>
#include <Qrect>
#include <QtGui>
#include <myapplication.h>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

#include <mywindow.h>

int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    myWindow w;

    w.show();

    return a.exec();
}

