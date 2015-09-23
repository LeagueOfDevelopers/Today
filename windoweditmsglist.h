#ifndef WINDOWEDITMSGLIST_H
#define WINDOWEDITMSGLIST_H

#include <QWidget>

namespace Ui {
class windowEditMsgList;
}

class windowEditMsgList : public QWidget
{
    Q_OBJECT

public:
    explicit windowEditMsgList(QWidget *parent = 0);
    ~windowEditMsgList();

public slots:
    void slotShow();

private:
    void mySetBackgroundColor();
    Ui::windowEditMsgList *ui;
};

#endif // WINDOWEDITMSGLIST_H
