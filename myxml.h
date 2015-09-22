#ifndef MYXML_H
#define MYXML_H

#include <QVector>
#include <QPair>
#include <QString>

namespace myXml
{
    enum type_operation
    {
        dislikeTrue,dislikeFalse,incrimentMessage
    };

    QVector < QPair <QString , int > > getMessages(bool = false);
    void modifyMessage(int num, enum type_operation);
    void addMessage(QString text);
}
#endif // MYXML_H
