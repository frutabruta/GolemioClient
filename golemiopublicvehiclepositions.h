#ifndef GOLEMIOPUBLICVEHICLEPOSITIONS_H
#define GOLEMIOPUBLICVEHICLEPOSITIONS_H

#include <QPointF>
#include <QJsonDocument>
#include <QJsonObject>

#include "golemiorequesthandler.h"


class VehiclePositionResult
{
public:
    VehiclePositionResult();
    VehiclePositionResult(QJsonDocument mVstupniJson);

    QPointF coordinates;
    QString gtfsTripId="";
    QString routeShortName="";
    QString originRouteName="";
    int runNumber=0;
    QString tripHeadsign="";
    QString routeType="";

    QString dumpToQString();
private:
    static QPointF geometryToQPointF(QJsonValue geometry);
};

class GolemioPublicVehiclePositions : public GolemioRequestHandler
{
    Q_OBJECT
public:
    GolemioPublicVehiclePositions(QByteArray klic);
    VehiclePositionResult parseMessage(QByteArray receivedMessage);
private slots:
    void slotMessageReceived(QByteArray message);
private:
signals:
    void signalDataParsed(VehiclePositionResult result);
};

#endif // GOLEMIOPUBLICVEHICLEPOSITIONS_H
