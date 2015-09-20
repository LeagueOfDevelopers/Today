#include "myapplication.h"
#include <QSettings>
#include <QSystemTrayIcon>

MyApplication::MyApplication(int argc,char* argv[]) : QApplication(argc, argv)
{
    if(!checkAutoload())
        setAutoload();
    loadSettings();
}

bool MyApplication::checkAutoload()
{
    return true;
}
void MyApplication::setAutoload()
{

}
void MyApplication::loadSettings()
{
    QSettings settings("lod","Today");

    QString look = settings.value("color").toString();

    if(settings.value("color").toInt()==0)
        settings.setValue("color","blue");

    if(settings.value("frequency").toInt()==0)
        settings.setValue("frequency",3);

}
void MyApplication::loadUpdates()
{

}
