#include "windoweditmsglist.h"
#include "ui_windoweditmsglist.h"
#include <QSettings>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>

windowEditMsgList::windowEditMsgList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::windowEditMsgList)
{
    mySetBackgroundColor();
    ui->setupUi(this);
}

void windowEditMsgList::slotShow()
{
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(10);
    for(int i = 0 ; i < 10; ++i)
    {
        QTableWidgetItem* pItem(new QTableWidgetItem(tr("blablabla")));
        pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
        pItem->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(i, 0, pItem);
    }

    show();
}

void windowEditMsgList::mySetBackgroundColor()
{
    QPalette pal;
    int nLight = 190;

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


windowEditMsgList::~windowEditMsgList()
{
    delete ui;
}
