#ifndef EMPTYCLASS_H
#define EMPTYCLASS_H

#include <QObject>

class emptyClass : public QObject
{
    Q_OBJECT
public:
    explicit emptyClass(QObject *parent = 0);

signals:

public slots:
    void slotButtonClicked();
};

#endif // EMPTYCLASS_H
