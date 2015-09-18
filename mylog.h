#ifndef MYLOG_H
#define MYLOG_H
#include <QTime>

namespace myLog
{
    void writeShowToLog(QTime);
    void readFromLog();
    void makeNewDay();
}

#endif // MYLOG_H
