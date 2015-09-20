#include <QObject>
#include <QDesktopWidget>
#include <QApplication>
#include <Qrect>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSettings>
#include <QSystemTrayIcon>

#include <myapplication.h>
#include <mywindow.h>
#include <myshowmanager.h>
#include <myxml.h>
#include <mylog.h>
#include <settings.h>


int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    myWindow w;
    myShowManager manager;
    Settings z;

    QObject::connect(&manager,SIGNAL(showMessage()),&w,SLOT(myShowMessage()));


    return a.exec();
}
