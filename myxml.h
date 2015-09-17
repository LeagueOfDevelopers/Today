#ifndef MYXML_H
#define MYXML_H

#include <QVector>
#include <QPair>
#include <QString>

namespace myXml
{

    QVector < QPair <QString , int > > getMessages();
    static void modifyMessage(int);
}
#endif // MYXML_H
