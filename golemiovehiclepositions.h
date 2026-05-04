#ifndef GOLEMIOVEHICLEPOSITIONS_H
#define GOLEMIOVEHICLEPOSITIONS_H

#include <QJsonDocument>
#include <QJsonObject>
#include "golemiorequesthandler.h"


class VehiclePositionResult
{
public:
    VehiclePositionResult();
    VehiclePositionResult(QJsonDocument mVstupniJson);

    //QPointF coordinates;
    QString gtfsTripId="";
    // QString routeShortName="";
    // QString originRouteName="";
    // int runNumber=0;
    // QString tripHeadsign="";
    // QString routeType="";

    // QString dumpToQString();
    QString dumpToQString();
private:
    //static QPointF geometryToQPointF(QJsonValue geometry);
};



class GolemioVehiclePositions : public GolemioRequestHandler
{
    Q_OBJECT
public:
    GolemioVehiclePositions(QByteArray key);
    VehiclePositionResult parseMessage(QByteArray receivedMessage);
public slots:
    void slotMessageReceived(QByteArray message);

signals:
    void signalDataParsed(VehiclePositionResult result);
};

#endif // GOLEMIOVEHICLEPOSITIONS_H
