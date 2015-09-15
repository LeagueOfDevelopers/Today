#include "emptyclass.h"
#include <Qt>
#include <QApplication>

emptyClass::emptyClass(QObject *parent) : QObject(parent)
{

}
void emptyClass::slotButtonClicked()
{
    qApp->exit();
}

