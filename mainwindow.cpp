#include "mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <ctime>
#include <Qrect>
#include <QtGui>

#include "ui_mainwindow.h"

void changing_window(MainWindow &__window);
void centerWidget(QWidget *widget);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowOpacity(0.8);
    ui->setupUi(this);
    changing_window(*this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void changing_window(MainWindow &__window)
{
    __window.setWindowFlags(Qt::FramelessWindowHint);
    QRect rec = QApplication::desktop()->availableGeometry();
    __window.resize(rec.width(),__window.height());
    centerWidget(&__window);
}

void centerWidget(QWidget *widget)
{
    QSize size = widget->sizeHint();
    QRect d = QApplication::desktop()->screenGeometry();
    QRect d1 = QApplication::desktop()->availableGeometry();
    widget->move(d.width()-d1.width(),(d.height()-(d.height()-d1.height()) - widget->height())/2);
}

