#include "mynetworkmanager.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkReply>
#include <string>

#include <myxml.h>

myNetworkManager::myNetworkManager(QObject *parent) : QObject(parent)
{
    UpdateMessages();
}

void myNetworkManager::AddMessage(QString sendText)
{

}
void myNetworkManager::UpdateMessages()
{
    file = new QFile(tr("download.html"));
    file->open(QIODevice::WriteOnly);

    QUrl url(tr("http://localhost/todayServ/?count=0"));

    reply = qnam.get(QNetworkRequest(url));
    QObject::connect(reply,SIGNAL(readyRead()),SLOT(slotReadHttpRequest()));
    QObject::connect(reply,SIGNAL(finished()),SLOT(slotHttpFinished()));
}

void myNetworkManager::slotHttpFinished()
{
    file->write(reply->readAll());

    file->close();

    myXml::uptadeBaseFromNet();

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;

}

void myNetworkManager::slotReadHttpRequest()
{
    if(file)
    {
        file->write(reply->readAll());
    }
}

