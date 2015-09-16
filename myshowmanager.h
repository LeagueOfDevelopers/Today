#ifndef MYSHOWMANAGER_H
#define MYSHOWMANAGER_H

#include <QObject>

class myShowManager : public QObject
{
    Q_OBJECT
private:
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
