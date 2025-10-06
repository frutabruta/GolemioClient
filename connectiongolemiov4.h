#ifndef CONNECTIONGOLEMIOV4_H
#define CONNECTIONGOLEMIOV4_H

#include "connectiongolemio.h"

class ConnectionGolemioV4 : public ConnectionGolemio
{
public:
    ConnectionGolemioV4();

    QStringList departureTimestampMinutes;
    QStringList icons;
    QString substitutionTextCs="";
    QString substitutionTextEn="";

};

#endif // CONNECTIONGOLEMIOV4_H
