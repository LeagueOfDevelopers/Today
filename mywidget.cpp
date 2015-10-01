#include "mywidget.h"

#include <QColor>
#include <QPalette>
#include <QSettings>
#include <QWidget>

myWidget::myWidget(QWidget *parent) : QWidget(parent)
{

}
void myWidget::mySetBackgroundColor(int Light = 190)
{
    QPalette pal;

    QSettings settings("lod","Today");
    QString color = settings.value("color").toString();

    if(color == "red")
    {
        pal.setColor(backgroundRole(),QColor(Qt::red).light(Light));
    }
    if(color == "blue")
    {
        pal.setColor(backgroundRole(),QColor(Qt::blue).light(Light));
    }
    if(color == "green")
    {
        pal.setColor(backgroundRole(),QColor(Qt::green).light(Light));
    }
    setPalette(pal);


}

