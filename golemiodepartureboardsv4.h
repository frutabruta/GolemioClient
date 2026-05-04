#ifndef GOLEMIODEPARTUREBOARDSV4_H
#define GOLEMIODEPARTUREBOARDSV4_H

#include "golemiodepartureboardsv2.h"

#include "connectiongolemiov4.h"


class GolemioDepartureBoardsV4 : public GolemioDepartureBoardsV2
{
public:
    GolemioDepartureBoardsV4(const QByteArray key);
    QVector<ConnectionGolemioV4> parseDomDocumentDepartures();
    QVector<ConnectionGolemioV4> seznamPrestupuGolemio;
};

#endif // GOLEMIODEPARTUREBOARDSV4_H
