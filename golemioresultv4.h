#ifndef GOLEMIORESULTV4_H
#define GOLEMIORESULTV4_H
#include <QObject>

#include "connectiongolemiov4.h"

class GolemioResultV4
{
public:
    GolemioResultV4();

    QString platform_code="";
    QString stop_name="";
    QStringList icons;

    QVector<ConnectionGolemioV4> connectionList;

};

#endif // GOLEMIORESULTV4_H
