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

private slots:

public slots:
    void slotShow();
    void slotApply();
    void slotDelete();
private:
    QVector<QDomNode> list;
    void mySetBackgroundColor();
    Ui::windowEditMsgList *ui;
};

#endif // WINDOWEDITMSGLIST_H
