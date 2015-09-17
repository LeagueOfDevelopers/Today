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

    void modifyMessage(int num)
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
        QDomNodeList roots = doc.elementsByTagName("node");
        if (roots.size() < num) {
           return;
        }
        QDomElement root = roots.at(num).toElement();
        root.setAttribute("dislike", "1");


        // Save content back to the file
        if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        file.write(xml);
        file.close();
    }
}
