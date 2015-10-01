#ifndef SETTINGSCOLOR_H
#define SETTINGSCOLOR_H

#include <QWidget>
#include <mywidget.h>

namespace Ui {
class SettingsColor;
}

class SettingsColor : public myWidget
{
    Q_OBJECT

public:
    explicit SettingsColor(QWidget *parent = 0);
    ~SettingsColor();

private slots:
    void slotButtonClicked();

private:
    Ui::SettingsColor *ui;
};

#endif // SETTINGSCOLOR_H
