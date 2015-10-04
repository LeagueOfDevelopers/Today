#include "mylog.h"
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QtXml>
#include <ctime>
#include <QSettings>
#include <QtAlgorithms>
#include <algorithm>
#include <string>

namespace myLog {

    bool checkNewDay()
    {
        QDomDocument doc("shows");
        QFile file("shows.xml");
        if (!file.open(QIODevice::ReadOnly)) {
            return true;
        }
        // Parse file
        if (!doc.setContent(&file)) {
           file.close();
           return true;
        }
        file.close();

        QDomElement dayNode = doc.elementsByTagName("day").item(0).toElement();
        QString lastDay = dayNode.attribute("date","");
        QString curDay = QDate::currentDate().toString("dd.MM.yyyy");

        return curDay == lastDay ? true : false;

    }

    void writeShowToLog(QTime inner)
    {
        QDomDocument doc("shows");
        QFile file("shows.xml");
        if (!file.open(QIODevice::ReadOnly)) {
            return;
        }
        // Parse file
        if (!doc.setContent(&file)) {
           file.close();
           return;
        }
        file.close();

        QDomElement last_show = doc.elementsByTagName("last_show").item(0).toElement();

        QString res = QString::number(inner.hour() ) + ":" + QString::number(inner.minute());
        last_show.setNodeValue(res);

        QDomElement newNodeTag = doc.createElement(QString("last_show"));
        QDomText newNodeText = doc.createTextNode(QString(res));
        newNodeTag.appendChild(newNodeText);

        // replace existing node with new node
        doc.documentElement().replaceChild(newNodeTag, last_show);

        QDomNodeList days = doc.elementsByTagName("day");
        if (days.size() < 1) {
           return;
        }
        QDomElement day = days.at(0).toElement();
        day.setAttribute("count",QString::number(day.attribute("count","").toInt() + 1));

        if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        file.write(xml);
        file.close();

    }

    void readFromLog()
    {
        QDomDocument doc("shows");
        QFile file("shows.xml");
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
        QDomNodeList days = doc.elementsByTagName("day");
        if (days.size() < 1) {
           return;
        }
        QDomElement day = days.at(0).toElement();

        QString cur_date = QDate::currentDate().toString("dd.MM.yyyy");
        QString day_date = day.attribute("date","");

        if(cur_date != day_date)
        {
            makeNewDay();
            return;
        }

        return;
    }

    void makeNewDay()
    {
        QDomDocument doc("shows");
        QFile file("shows.xml");
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
        QDomNodeList days = doc.elementsByTagName("day");
        if (days.size() < 1) {
           return;
        }
        QDomElement day = days.at(0).toElement();
        QString cur_date = QDate::currentDate().toString("dd.MM.yyyy");

        day.setAttribute("date",cur_date);
        day.setAttribute("count",QString::number(0));

        srand(time(NULL));
        QSettings settings("lod","Today");

        QVector < QPair < int, int > > planTime;

        qsrand(time(NULL));

        for(int i = 0 ; i < settings.value("frequency").toInt();++i)
        {
            int fir = qrand()%24;
            int sec = qrand()%60;
            planTime.push_back(qMakePair(fir,sec));
        }

        std::sort(planTime.begin(),planTime.end());


        QDomNodeList new_magic = doc.elementsByTagName("showing");

        while(new_magic.size())
        {
            QDomNode magic = new_magic.item(0);
            magic.parentNode().removeChild(magic);
        }

        QDomNode plan_today = doc.elementsByTagName("plan_today").item(0);

        for(int i = 0 ; i < planTime.size(); ++i)
        {
            QDomElement inserting = doc.createElement("showing");
            inserting.setAttribute("time", QString::number(planTime[i].first)+":"+QString::number(planTime[i].second));
            plan_today.appendChild(inserting);
        }

        QFile new_file("shows.xml");
        if (!new_file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        new_file.write(xml);
        new_file.close();
    }

    int getCountCurDay()
    {
        QDomDocument doc("shows");
        QFile file("shows.xml");
        if (!file.open(QIODevice::ReadOnly)) {
            return 0;
        }
        // Parse file
        if (!doc.setContent(&file)) {
           file.close();
           return 0;
        }
        file.close();

        QDomNodeList days = doc.elementsByTagName("day");
        if (days.size() < 1) {
           return 0;
        }
        QDomElement day = days.at(0).toElement();
        return day.attribute("count","").toInt();
    }

    QTime getLastTime()
    {
        QDomDocument doc("shows");
        QFile file("shows.xml");

        QTime outing;
        outing.setHMS(0,0,0);


        if (!file.open(QIODevice::ReadOnly)) {
            return outing;
        }
        // Parse file
        if (!doc.setContent(&file)) {
           file.close();
           return outing;
        }
        file.close();

        // Modify content
        QDomNodeList elems = doc.elementsByTagName("last_show");
        if (elems.size() < 1) {
           return outing;
        }
        QDomElement last_show = elems.at(0).toElement();

        QString oldtext = last_show.text();
        std::string text = oldtext.toStdString();
        QString fir,sec;
        bool flag = false;
        for(unsigned int i = 0; i < text.size(); ++i)
        {
            if(text[i] == ':')
            {
                flag = true;
                continue;
            }
            if(!flag)
                fir += text[i];
            else
                sec += text[i];
        }
        outing.setHMS(fir.toInt(),sec.toInt(),0);
        return outing;

    }

    QTime getPlanTime(int pointer)
    {
        QDomDocument doc("shows");
        QFile file("shows.xml");

        QTime outing;
        outing.setHMS(0,0,0);

        if (!file.open(QIODevice::ReadOnly)) {
            return outing;
        }
        // Parse file
        if (!doc.setContent(&file)) {
           file.close();
           return outing;
        }
        file.close();


        QDomNode plan_today = doc.elementsByTagName("plan_today").item(0);

        QDomNode magic = plan_today.firstChild();

        while(!magic.isNull() && pointer)
        {
            magic = magic.nextSibling();
            --pointer;
        }



        QDomNode node = magic;


        std::string text = node.toElement().attribute("time","").toStdString();
        QString fir,sec;
        bool flag = false;
        for(unsigned int i = 0; i < text.size(); ++i)
        {
            if(text[i] == ':')
            {
                flag = true;
                continue;
            }
            if(!flag)
                fir += text[i];
            else
                sec += text[i];
        }
        outing.setHMS(fir.toInt(),sec.toInt(),0);
        return outing;


    }
}
