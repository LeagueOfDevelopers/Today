#include "windoweditmsglist.h"
#include "ui_windoweditmsglist.h"
#include <QSettings>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <myxml.h>


windowEditMsgList::windowEditMsgList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::windowEditMsgList)
{
    mySetBackgroundColor();
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(slotApply()));
}

void windowEditMsgList::slotApply()
{
    QVector < QPair < QString, int > > outing(list.size());
    for(int i = 0 ; i < list.size(); ++i)
    {
        QString aaa = ui->tableWidget->item(i,0)->text();
        int dislike = ui->tableWidget->item(i,0)->checkState();

        outing[i] = qMakePair(aaa,dislike == Qt::Checked ? 0 : 1);
    }
    myXml::modifyBase(list,outing);
}

void windowEditMsgList::slotShow()
{
    list = myXml::getAllMsg();

    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(list.size());
    for(int i = 0 ; i < list.size(); ++i)
    {
        QTableWidgetItem* pItem(new QTableWidgetItem(list[i].childNodes().item(0).toElement().text()));
        pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
        if(list[i].toElement().attribute("dislike","")!=QString("0"))
           pItem->setCheckState(Qt::Unchecked);
        else
           pItem->setCheckState(Qt::Checked);
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
