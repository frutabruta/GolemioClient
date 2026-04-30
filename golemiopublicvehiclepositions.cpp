#include "golemiopublicvehiclepositions.h"



GolemioPublicVehiclePositions::GolemioPublicVehiclePositions(QByteArray klic) : GolemioRequestHandler(klic)
{
    mAdresa="https://api.golemio.cz/v2/public/vehiclepositions/";

    connect(this,&GolemioRequestHandler::signalReceivedData,this,&GolemioPublicVehiclePositions::slotMessageReceived);
}


void GolemioPublicVehiclePositions::slotMessageReceived(QByteArray message)
{
    VehiclePositionResult result=parseMessage(message);


    qDebug().noquote()<<result.dumpToQString();

    emit signalDataParsed(result);
}

VehiclePositionResult GolemioPublicVehiclePositions::parseMessage(QByteArray receivedMessage)
{
    VehiclePositionResult result;

    QJsonDocument mVstupniJson=QJsonDocument::fromJson(receivedMessage);

    result=VehiclePositionResult(mVstupniJson);

    return result;
}

VehiclePositionResult::VehiclePositionResult()
{

}

VehiclePositionResult::VehiclePositionResult(QJsonDocument mVstupniJson)
{
    gtfsTripId=mVstupniJson["gtfs_trip_id"].toString();
    routeType=mVstupniJson["route_type"].toString();
    routeShortName=mVstupniJson["route_short_name"].toString();
    originRouteName=mVstupniJson["origin_route_name"].toString();
    runNumber=mVstupniJson["run_number"].toInt();
    tripHeadsign=mVstupniJson["trip_headsign"].toString();
    //result.=mVstupniJson[""].toString();
    coordinates=geometryToQPointF(mVstupniJson["geometry"]);
}

QString VehiclePositionResult::dumpToQString()
{
    QString result;
    result+="gtfs_trip_id: "+gtfsTripId+"\n";
    result+="route_type: "+routeType+"\n";
    result+="route_short_name: "+routeShortName+"\n";
    result+="origin_route_name: "+originRouteName+"\n";
    result+="run_number: "+QString::number(runNumber)+"\n";
    result+="trip_headsign: "+tripHeadsign+"\n";
    result+="geometry: "+QString::number(coordinates.x())+","+QString::number(coordinates.y())+"\n";
    return result;
}



QPointF VehiclePositionResult::geometryToQPointF(QJsonValue geometry)
{

    return QPointF(geometry["coordinates"][0].toDouble(),geometry["coordinates"][1].toDouble());
}
