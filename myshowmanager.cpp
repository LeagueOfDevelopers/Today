#include "myshowmanager.h"
#include <QSettings>
#include <QTimer>
#include <QTime>
#include <QDate>
#include <mylog.h>

myShowManager::myShowManager(QObject *parent) : QObject(parent)
{
    countShows = myLog::getCountCurDay();
    last_time = myLog::getLastTime();
    start_time = QDateTime::currentDateTime();
    plan_showing = myLog::getPlanTime(countShows);

    readLog();

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(checkTime()));
    timer->start(15000);
}
void myShowManager::writeToLog()
{

}
void myShowManager::readLog()
{

}
void myShowManager::checkTime()
{
    QDateTime a = QDateTime::currentDateTime();
    unsigned long long int z = a.toTime_t() - start_time.toTime_t();
    if(z/1000 < 60)
        return;

    if(QTime::currentTime() > plan_showing)
    {
        QSettings settings("lod","Today");
        if(countShows == settings.value("frequency").toInt())
            return;

        QTime b;
        b.setHMS(0,30,0);

        if( (QTime::currentTime().elapsed() - last_time.elapsed()) > b.elapsed())
        if(checkAvaiableShowing())
        {
            ++countShows;
            myLog::writeShowToLog(QTime::currentTime());
            plan_showing = myLog::getPlanTime(countShows);
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
