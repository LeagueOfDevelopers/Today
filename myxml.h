#ifndef MYXML_H
#define MYXML_H

#define DELETING_MSG "Удалить"

#include <QVector>
#include <QPair>
#include <QString>
#include <QDomNode>
#include <QPair>

namespace myXml
{
    enum type_operation
    {
        dislikeTrue,dislikeFalse,incrimentMessage
    };

    QVector < QPair <QString , int > > getMessages(bool = false);
    QVector < QDomNode >getAllMsg();
    QVector < QPair < int , QString > > myParseHtml(QString text);

    QPair < int , QString > myParseRow(QString text);

    void uptadeBaseFromNet();
    void modifyMessage(int num, enum type_operation);
    void addMessage(QString text, int numInBase = -1);
    void modifyBase ( QVector < QDomNode > , QVector < QPair <QString , int > > );
}
#endif // MYXML_H
