#include "windowaddmsg.h"
#include "ui_windowaddmsg.h"
#include <myxml.h>
#include <QSettings>

windowAddMsg::windowAddMsg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::windowAddMsg)
{
    ui->setupUi(this);
    connect(ui->buttonSend,SIGNAL(clicked(bool)),this,SLOT(slotApply()));
    mySetBackgroundColor();
}


void windowAddMsg::slotShow()
{
    show();
}

void windowAddMsg::slotApply()
{
    QString send_text = ui->textEdit->toPlainText();
    if(!ui->checkBoxSendToUser->isTristate())
    {
        myXml::addMessage(send_text);
    }
    //Тут нужна обработка чекбокса отправки на сервер
    hide();
}

void windowAddMsg::mySetBackgroundColor()
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

windowAddMsg::~windowAddMsg()
{
    delete ui;
}
