#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class myWindow : public QWidget
{
    Q_OBJECT
private:
    void mySetBackgroundColor();
    void mySetPosition();
    void setElems();
public:
    explicit myWindow(QWidget *parent = 0);

signals:

public slots:

};

#endif // WINDOW_H
