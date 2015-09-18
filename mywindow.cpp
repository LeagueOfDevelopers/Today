#include "mywindow.h"
#include <QSettings>
#include <QDesktopWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <myxml.h>
#include <mylog.h>

myWindow::myWindow(QWidget *parent) : QWidget(parent)
{

    mySetBackgroundColor();
    mySetPosition();
    setElems();
}

void myWindow::mySetBackgroundColor()
{
    QPalette pal;
    int nLight = 150;

    QSettings settings("lod","Today");
    QString color = settings.value("color").toString();

    if(color == "red")
    {
        pal.setColor(backgroundRole(),QColor(Qt::red).light(nLight));
    }
    if(color == "blue")
    {
        pal.setColor(backgroundRole(),QColor(Qt::blue).light(nLight));
    }
    if(color == "green")
    {
        pal.setColor(backgroundRole(),QColor(Qt::green).light(nLight));
    }
    setPalette(pal);

}

void myWindow::mySetPosition()
{
    QDesktopWidget desktop;
    int desktopHeight=desktop.geometry().height();
    int desktopWidth=desktop.geometry().width();

    int availableDesktopHeight=desktop.availableGeometry().height();
    int availableDesktopWidth=desktop.availableGeometry().width();

    int x = desktopWidth - availableDesktopWidth;
    int y = desktopHeight - availableDesktopHeight;

    move(x,y);
    resize(availableDesktopWidth,availableDesktopHeight/3);
}

void myWindow::setElems()
{
    like = new QPushButton("like");
    dislike = new QPushButton("dislike");
    label = new QLabel;

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    QHBoxLayout* phbxLayout = new QHBoxLayout;

    phbxLayout->addWidget(like);
    phbxLayout->addWidget(dislike);

    pvbxLayout->addWidget(label);
    pvbxLayout->addLayout(phbxLayout);

    setLayout(pvbxLayout);

}

void myWindow::myHide()
{
    hide();
}

void myWindow::myShowMessage()
{
    QVector < QPair < QString, int > > mas = myXml::getMessages();

    //Тут надо рандомчик подкинуть

    QString showText = mas[0].first;
    label->setText(showText);
    show();
    QTimer::singleShot(10000,this,SLOT(myHide()));
    myLog::writeShowToLog(QTime::currentTime());

}
