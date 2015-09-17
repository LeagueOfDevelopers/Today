#include "myxml.h"
#include <QtXml/QXmlReader>
#include <QFile>
#include <Qt>
#include <QtXml/QDomDocument>
#include <QErrorMessage>

namespace myXml
{

    QVector< QPair < QString, int > > getMessages(bool my_own)
    {
        QVector < QPair < QString, int > > outing;

        QFile file("messages.xml");
        QDomDocument domDoc;

        if(!file.open(QIODevice::ReadOnly))
        {
            return outing;
        }

        if(!domDoc.setContent(&file))
        {
            file.close();
            return outing;
        }

        QDomElement n = domDoc.documentElement();
        QDomNode domNode = n.firstChild();

        while(!domNode.isNull())
        {
            if(!domNode.isElement())
                continue;
            QDomElement e = domNode.toElement();
            if(e.tagName() != "node")
                continue;

            if(e.attribute("dislike","") == "0")
                outing.push_back(qMakePair(e.childNodes().item(0).toElement().text(),e.attribute("num","").toInt()));
            domNode = domNode.nextSibling();
        }

        return outing;
    }

    void modifyMessage(int num, type_operation myType = type_operation::dislikeTrue)
    {
        QDomDocument doc("messages");
        QFile file("messages.xml");
        if (!file.open(QIODevice::ReadOnly)) {
            return;
        }
        // Parse file
        if (!doc.setContent(&file)) {
           file.close();
           return;
        }
        file.close();

        // Modify content
        QDomNodeList nodes = doc.elementsByTagName("node");
        if (nodes.size() < num) {
           return;
        }
        QDomElement node = nodes.at(num).toElement();

        if(myType == type_operation::dislikeTrue)
            node.setAttribute("dislike", "1");
        if(myType == type_operation::dislikeFalse)
            node.setAttribute("dislike", "0");
        if(myType == type_operation::incrimentMessage)
        {
            int buf = node.attribute("shows","").toInt();
            node.setAttribute("dislike", QString::number(buf+1));
        }
        // Save content back to the file
        if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        file.write(xml);
        file.close();
    }
}
