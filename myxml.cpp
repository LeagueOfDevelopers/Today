#include "myxml.h"
#include <QtXml/QXmlReader>
#include <QFile>
#include <Qt>
#include <QtXml/QDomDocument>
#include <QErrorMessage>
#include <QString>

namespace myXml
{

    void uptadeBaseFromNet()
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

        file.setFileName("download.html");
        file.open(QIODevice::ReadOnly);

        QString look(file.readAll());
        QVector < QPair <int , QString > > newMessages = myParseHtml(look);

        for(int i = 0 ; i < newMessages.size(); ++i)
            myXml::addMessage(newMessages[i].second, newMessages[i].first);

    }

    QVector < QPair < int , QString > > myParseHtml(QString text)
    {
        QString beginTr = "<tr>";
        QString endTr = "</tr>";

        bool insideTr = false;
        QString buf = "";

        QVector< QString > rows;

        for(int i = 0 ; i < text.size(); ++i)
        {
            if(insideTr)
            {
                if(text.mid(i,endTr.size()) == endTr)
                {
                    rows.push_back(buf);
                    buf = "";
                    insideTr = false;
                    continue;
                }
                buf += text[i];
            }
            else
            {
                if(text.mid(i,beginTr.size()) == beginTr)
                {
                    insideTr = true;
                }
            }
        }

        QVector < QPair < int, QString > > ans;

        for(int i = 0 ; i < rows.size(); ++i)
        {
            QPair< int, QString> buf =  myParseRow(rows[i]);
            ans.push_back(buf);
        }
        return ans;
    }

    QPair < int , QString > myParseRow(QString text)
    {
        QPair<int, QString > ans;

        QString beginTd = "<td>";
        QString endTd = "</td>";

        QString buf = "";
        int num = -1, count = 0;

        bool insideTd = false;

        for(int i = 0 ; i < text.size(); ++i)
        {
            if(insideTd)
            {
                if(text.mid(i,endTd.size()) == endTd)
                {
                    if(count == 0)
                    {
                        num = buf.toInt();
                        buf = "";
                        ++count;
                        insideTd = false;
                        continue;
                    }
                    else
                    {
                        ans.first = num;
                        ans.second = buf;
                        return ans;
                    }
                }
                else
                {
                    buf += text[i];
                }
            }
            else
            {
                if(text.mid(i,beginTd.size()) == beginTd)
                {
                    i+= beginTd.size();
                    --i;
                    insideTd = true;
                    continue;
                }
            }
        }


        return ans;
    }

    void modifyBase(QVector<QDomNode> inlist, QVector<QPair<QString, int> >inVectorPair)
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

        for(int i = 0 ; i < inlist.size(); ++i)
        {
            for(int j = 0; j < nodes.size(); ++j)
            {
                if(inlist[i].toElement().attribute("num","") == nodes.item(j).toElement().attribute("num",""))
                {
                    QDomNode newNode = doc.createElement("node");
                    newNode.toElement().setAttribute("num",inlist[i].toElement().attribute("num",""));
                    newNode.toElement().setAttribute("num_in_base",inlist[i].toElement().attribute("num_in_base",""));
                    newNode.toElement().setAttribute("shows",inlist[i].toElement().attribute("shows","").toInt());
                    newNode.toElement().setAttribute("dislike",inVectorPair[i].second);

                    QDomNode textNode = doc.createElement("text");
                    QDomText newText = doc.createTextNode(inVectorPair[i].first);
                    textNode.appendChild(newText);
                    newNode.appendChild(textNode);
                    doc.elementsByTagName("big_node").item(0).toElement().replaceChild(newNode,nodes.item(j));

                    break;
                }
            }
        }

        for(int j = 0; j < nodes.size(); ++j)
        {
            if(nodes.item(j).childNodes().item(0).toElement().text()==QString(DELETING_MSG))
                nodes.item(j).parentNode().removeChild(nodes.item(j));
        }

        // Save content back to the file
        if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        file.write(xml);
        file.close();


        return;
    }

    QVector< QDomNode > getAllMsg()
    {
        QVector< QDomNode > outing;

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

            outing.push_back(domNode);
            domNode = domNode.nextSibling();
        }
        return outing;

    }

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

            if(my_own == true && e.attribute("num_in_base","")!= "-1")
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

    void addMessage(QString text, int numInBase)
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

        int numNewNode = nodes.item(nodes.size()-1).toElement().attribute("num","").toInt()+1;
        int numInBaseNewNode = numInBase;
        int showsNewNode = 0;
        int dislikeNewNode = 0;

        QDomNode big_node = doc.elementsByTagName("big_node").item(0);

        QDomNode newNode = doc.createElement("node");
        newNode.setNodeValue(text);
        QDomElement newNodeElem = newNode.toElement();
        newNodeElem.setAttribute("dislike",dislikeNewNode);
        newNodeElem.setAttribute("num",numNewNode);
        newNodeElem.setAttribute("num_in_base",numInBaseNewNode);
        newNodeElem.setAttribute("shows",showsNewNode);

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
