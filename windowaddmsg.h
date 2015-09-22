#ifndef WINDOWADDMSG_H
#define WINDOWADDMSG_H

#include <QWidget>

namespace Ui {
class windowAddMsg;
}

class windowAddMsg : public QWidget
{
    Q_OBJECT

public:
    explicit windowAddMsg(QWidget *parent = 0);
    ~windowAddMsg();

private:
    Ui::windowAddMsg *ui;
    void mySetBackgroundColor();
public slots:
    void slotShow();
private slots:
    void slotApply();

};

#endif // WINDOWADDMSG_H
