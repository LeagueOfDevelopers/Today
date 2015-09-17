#include "myxml.h"
#include <QtXml/QXmlReader>
#include <QFile>
#include <Qt>
#include <QtXml/QDomDocument>

namespace myXml
{
    QVector< QPair < QString, int > > getMessages()
    {
        QVector < QPair < QString, int > > outing;
        QFile file("messages.xml");
        QDomDocument domDoc;

        if(file.open(QIODevice::ReadOnly))
        {
            if(domDoc.setContent(&file))
            {
                QDomElement n = domDoc.documentElement();
                QDomNode domNode = n.firstChild();
                while(!domNode.isNull())
                {
                    if(domNode.isElement())
                    {
                        QDomElement e = domNode.toElement();
                        if(e.tagName() == "node")
                        {
                            QDomNodeList listNodes = domNode.childNodes();
                            QDomNode node = listNodes.item(1);

                            e = node.toElement();
                            QString look = e.text();

                            if(look == "0")
                            {
                                node = listNodes.item(0);
                                QString mytext = node.toElement().text();
                                int num = listNodes.item(0).toElement().text().toInt();
                                outing.push_back(qMakePair(mytext,num));

                            }
                        }
                    }
                    domNode = domNode.nextSibling();
                }
            }
        }



        return outing;
    }
    void modifyMessage(int num)
    {

    }
}
