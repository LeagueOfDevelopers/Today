#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class myWidget : public QWidget
{
    Q_OBJECT
protected:
    void mySetBackgroundColor(int);

public:
    explicit myWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // MYWIDGET_H
