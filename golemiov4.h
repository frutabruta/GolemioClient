#ifndef GOLEMIOV4_H
#define GOLEMIOV4_H

#include "golemiodepartureboardsv2.h"

#include "connectiongolemiov4.h"


class GolemioV4 : public GolemioDepartureBoardsV2
{
public:
    GolemioV4(const QByteArray key);
    QVector<ConnectionGolemioV4> parseDomDocumentDepartures();

    QVector<ConnectionGolemioV4> seznamPrestupuGolemio;
};

#endif // GOLEMIOV4_H
