#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QPushButton>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    QPushButton* returnButtonToAddMsg();
    QPushButton* returnButtonEditMsg();


private:
    Ui::Settings *ui;
    void mySetBackgroundColor();

private slots:
    void changeEvent(QEvent*);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();
    void slotApply();
    void slotCancel();
private:
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;

};

#endif // SETTINGS_H
