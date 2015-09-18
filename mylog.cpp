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

namespace myLog {

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


        QFile new_file("shows.xml");
        if (!new_file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        new_file.write(xml);
        new_file.close();

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

        // Save content back to the file
        if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            return;
        }
        QByteArray xml = doc.toByteArray();
        file.write(xml);
        file.close();
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
}