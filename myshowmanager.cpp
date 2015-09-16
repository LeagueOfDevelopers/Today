#include "myshowmanager.h"
#include <QTimer>

myShowManager::myShowManager(QObject *parent) : QObject(parent)
{
    readLog();

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(checkTime()));
    timer->start(1000);
}
void myShowManager::writeToLog()
{

}
void myShowManager::readLog()
{

}
void myShowManager::checkTime()
{
    //Тут условие того, что мы попали в нужное время
    if(true)
    {
        if(checkAvaiableShowing())
        {
            writeToLog();
            emit showMessage();
        }
    }
}

void myShowManager::setTime()
{

}
bool myShowManager::checkAvaiableShowing()
{
    return true;

}
