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
#include <settingscolor.h>

int main(int argc, char *argv[])
{
    myLog::makeNewDay();
    MyApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(false);

    myWindow w;
    myShowManager m;
    Settings z;
    windowAddMsg x;
    windowEditMsgList q;
    SettingsColor g;


    QObject::connect(&m,SIGNAL(showMessage()),&w,SLOT(myShowMessage()));
    QObject::connect(z.returnButtonToAddMsg(),SIGNAL(clicked(bool)),&x,SLOT(show()));
    QObject::connect(z.returnButtonEditMsg(),SIGNAL(clicked(bool)),&q,SLOT(slotShow()));
    QObject::connect(z.returnButtonColorEdit(),SIGNAL(clicked(bool)),&g,SLOT(show()));

    return a.exec();
}
