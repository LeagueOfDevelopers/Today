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

    void modifyMessage(int num, type_operation myType = dislikeTrue)
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

        if(myType == dislikeTrue)
            node.setAttribute("dislike", "1");
        if(myType == dislikeFalse)
            node.setAttribute("dislike", "0");
        if(myType == incrimentMessage)
        {
            int buf = node.attribute("shows","").toInt();
            node.setAttribute("shows", QString::number(buf+1));
        }
        // Save content back to the file
        if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        file.write(xml);
        file.close();
    }

    void addMessage(QString text)
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

        int numNewNode = nodes.size()+1;
        int numInBaseNewNode = -1;
        int showsNewNode = 0;
        int dislikeNewNode = 0;

        QDomNode big_node = doc.elementsByTagName("big_node").item(0);

        QDomNode newNode = doc.createElement("node");
        newNode.setNodeValue(text);
        QDomElement newNodeElem = newNode.toElement();
        newNodeElem.setAttribute("dislike",dislikeNewNode);
        newNodeElem.setAttribute("num",numNewNode);
        newNodeElem.setAttribute("num_in_base",numInBaseNewNode);

        QDomNode newNodeText = doc.createElement("text");
        QDomText newNodeTextValue = doc.createTextNode(text);

        newNodeText.appendChild(newNodeTextValue);

        newNode.appendChild(newNodeText);

        big_node.appendChild(newNode);

        // Save content back to the file
        if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        file.write(xml);
        file.close();
    }
}
