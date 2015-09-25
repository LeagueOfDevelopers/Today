#ifndef WINDOW_H
#define WINDOW_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>

class myWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton *like;
    QPushButton *dislike;
    QLabel *label;

    void mySetBackgroundColor();
    void mySetPosition();
    void setElems();
    void mySetFont();
    void setMyLabelStyle();
public:
    explicit myWindow(QWidget *parent = 0);

signals:

public slots:
    void myShowMessage();
    void myHide();
};

#endif // WINDOW_H
