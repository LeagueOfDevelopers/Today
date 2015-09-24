#ifndef WINDOWEDITMSGLIST_H
#define WINDOWEDITMSGLIST_H

#include <QWidget>
#include <QDomNode>

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
    void slotApply();
private:
    QVector<QDomNode> list;
    void mySetBackgroundColor();
    Ui::windowEditMsgList *ui;
};

#endif // WINDOWEDITMSGLIST_H
