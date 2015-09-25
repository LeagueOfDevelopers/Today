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
    if(myLog::checkNewDay())
        myLog::makeNewDay();

}
void myShowManager::checkTime()
{
    //СДЕЛАТЬ ПРОВЕРКУ НА ВХОЖДЕНИЕ В НОВЫЕ СУТКИ!

    QDateTime a = QDateTime::currentDateTime();
    unsigned long long int z = a.toTime_t() - start_time.toTime_t();
    //всунули костыль для теста
    if(z < 60)
        return;

    if(QTime::currentTime() > plan_showing)
    {
        QSettings settings("lod","Today");
        if(countShows == settings.value("frequency").toInt())
            return;

        QTime b;

        int hours = settings.value("periodShows").toInt()/60;
        int minutes = settings.value("periodShows").toInt() - hours*60;
        b.setHMS(hours,minutes,0);

        if( (QTime::currentTime().elapsed() - last_time.elapsed()) > b.elapsed() || countShows == 0)
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
