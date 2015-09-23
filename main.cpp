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
#include <windowaddmsg.h>
#include <windoweditmsglist.h>

int main(int argc, char *argv[])
{
    myLog::makeNewDay();
    MyApplication a(argc, argv);
    myWindow w;
    myShowManager manager;
    Settings z;
    windowAddMsg x;
    windowEditMsgList q;

    QObject::connect(&manager,SIGNAL(showMessage()),&w,SLOT(myShowMessage()));
    QObject::connect(z.returnButtonToAddMsg(),SIGNAL(clicked(bool)),&x,SLOT(show()));
    QObject::connect(z.returnButtonEditMsg(),SIGNAL(clicked(bool)),&q,SLOT(slotShow()));

    return a.exec();
}
