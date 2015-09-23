#include "settings.h"
#include "ui_settings.h"
#include <QSettings>
#include <QDialogButtonBox>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this -> setTrayIconActions();
    this -> showTrayIcon();

    mySetBackgroundColor();

    QSettings _settings("lod","Today");

    ui->sliderTimeBetweenShows->setRange(5,360);
    ui->sliderTimeBetweenShows->setSingleStep(5);
    ui->sliderShows->setRange(1,50);

    ui->sliderShows->setValue(_settings.value("frequency","").toInt());
    ui->sliderTimeBetweenShows->setValue(_settings.value("periodShows","").toInt());


    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(slotApply()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(slotCancel()));
}

QPushButton* Settings::returnButtonToAddMsg()
{
    return ui->addMsgButton;
}

QPushButton* Settings::returnButtonEditMsg()
{
    return ui->editMsgButton;
}

void Settings::slotCancel()
{
    QSettings _settings("lod","Today");

    int oldTimeShows = _settings.value("periodShows","").toInt();
    int oldCountShows = _settings.value("frequency","").toInt();

    ui->sliderShows->setValue(oldCountShows);
    ui->sliderTimeBetweenShows->setValue(oldTimeShows);

}

void Settings::slotApply()
{
    /*
     * Принять изменения в регистре
     * Прописать логику изменения базы и настроек
     * */

    QSettings _settings("lod","Today");

    int newTimeShows = ui->sliderTimeBetweenShows->value();
    int newCountShows = ui->sliderShows->value();

    _settings.setValue("frequency",newCountShows);
    _settings.setValue("periodShows",newTimeShows);

    return;
}

void Settings::showTrayIcon()
{
    // Создаём экземпляр класса и задаём его свойства...
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/true_icon.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(trayIconMenu);

    // Подключаем обработчик клика по иконке...
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    // Выводим значок...
    trayIcon -> show();
}

void Settings::mySetBackgroundColor()
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

void Settings::trayActionExecute()
{
    show();
}

void Settings::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this -> trayActionExecute();
            break;
        default:
            break;
    }
}

void Settings::setTrayIconActions()
{
    // Setting actions...
    restoreAction = new QAction("Настройки", this);
    quitAction = new QAction("Выход", this);

    // Connecting actions to slots...
    connect (restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Setting system tray's icon menu...
    trayIconMenu = new QMenu(this);
    trayIconMenu -> addAction (restoreAction);
    trayIconMenu -> addAction (quitAction);
}

void Settings::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event -> type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            this -> hide();
        }
    }
}

Settings::~Settings()
{
    delete ui;
}
