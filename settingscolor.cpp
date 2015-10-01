#include "settingscolor.h"
#include "ui_settingscolor.h"

#include <mywidget.h>
#include <QSettings>

SettingsColor::SettingsColor(QWidget *parent) :
    myWidget(parent),
    ui(new Ui::SettingsColor)
{
    ui->setupUi(this);

    setFixedSize(size());

    mySetBackgroundColor(190);

    connect(ui->Red,SIGNAL(clicked(bool)),SLOT(slotButtonClicked()));
    connect(ui->Green,SIGNAL(clicked(bool)),SLOT(slotButtonClicked()));
    connect(ui->Blue,SIGNAL(clicked(bool)),SLOT(slotButtonClicked()));

}

void SettingsColor::slotButtonClicked()
{    QObject *senderObj = sender(); // This will give Sender object
     QString senderObjName = senderObj->objectName();

      QSettings settings("lod","Today");
      QString color = settings.value("color").toString();

      if(senderObjName == "Red")
      {
          settings.setValue("color","red");
      }
      if(senderObjName == "Blue")
      {
          settings.setValue("color","blue");
      }
      if(senderObjName == "Green")
      {
          settings.setValue("color","green");
      }

      mySetBackgroundColor(190);
}

SettingsColor::~SettingsColor()
{
    delete ui;
}
