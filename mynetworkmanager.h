#ifndef MYNETWORKMANAGER_H
#define MYNETWORKMANAGER_H

#include <QObject>

class myNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit myNetworkManager(QObject *parent = 0);

signals:

public slots:
};

#endif // MYNETWORKMANAGER_H
