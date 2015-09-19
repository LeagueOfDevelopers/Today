#ifndef MYSHOWMANAGER_H
#define MYSHOWMANAGER_H

#include <QObject>
#include <QTime>
#include <QDate>
#include <QDateTime>

class myShowManager : public QObject
{
    Q_OBJECT
private:
    int countShows;
    QTime last_time;
    QTime plan_showing;
    QDateTime start_time;


    void readLog();
    void writeToLog();
    void setTime();
    bool checkAvaiableShowing();
public:
    explicit myShowManager(QObject *parent = 0);

signals:
    void showMessage();

public slots:
    void checkTime();

};

#endif // MYSHOWMANAGER_H
