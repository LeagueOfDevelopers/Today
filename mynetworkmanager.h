#ifndef MYNETWORKMANAGER_H
#define MYNETWORKMANAGER_H

#include <QObject>
#include <QFile>
#include <QtNetwork/QNetworkReply>

class myNetworkManager : public QObject
{
    Q_OBJECT
private:
    void UpdateMessages();
    QFile *file;
    QNetworkReply *reply;
    QNetworkAccessManager qnam;

public:
    explicit myNetworkManager(QObject *parent = 0);

signals:

private slots:
    void slotReadHttpRequest();
    void slotHttpFinished();
public slots:
    void AddMessage(QString sendText);

};

#endif // MYNETWORKMANAGER_H
