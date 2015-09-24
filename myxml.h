#ifndef MYXML_H
#define MYXML_H

#define DELETING_MSG "Удалить"

#include <QVector>
#include <QPair>
#include <QString>
#include <QDomNode>

namespace myXml
{
    enum type_operation
    {
        dislikeTrue,dislikeFalse,incrimentMessage
    };

    QVector < QPair <QString , int > > getMessages(bool = false);
    void modifyMessage(int num, enum type_operation);
    void addMessage(QString text);
    QVector < QDomNode >getAllMsg();
    void modifyBase ( QVector < QDomNode > , QVector < QPair <QString , int > > );
}
#endif // MYXML_H
