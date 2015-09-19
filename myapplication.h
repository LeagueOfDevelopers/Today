#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QObject>
#include <QApplication>

class MyApplication : public QApplication
{
    Q_OBJECT
private:
    bool checkAutoload();
    void setAutoload();
    void loadSettings();
    void loadUpdates();
public:
    MyApplication(int,char* []);
signals:
public slots:
};

#endif // MYAPPLICATION_H
