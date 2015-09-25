#ifndef MYLOG_H
#define MYLOG_H
#include <QTime>

namespace myLog
{
    void writeShowToLog(QTime);
    void readFromLog();
    void makeNewDay();
    bool checkNewDay();
    int getCountCurDay();
    QTime getLastTime();
    QTime getPlanTime(int);
}

#endif // MYLOG_H
