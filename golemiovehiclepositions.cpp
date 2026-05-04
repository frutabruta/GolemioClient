#include "golemiovehiclepositions.h"


GolemioVehiclePositions::GolemioVehiclePositions(QByteArray klic) : GolemioRequestHandler(klic)
{
    mAddress="https://api.golemio.cz/v2/vehiclepositions/";

    connect(this,&GolemioRequestHandler::signalReceivedData,this,&GolemioVehiclePositions::slotMessageReceived);
}


void GolemioVehiclePositions::slotMessageReceived(QByteArray message)
{
    VehiclePositionResult result=parseMessage(message);


    qDebug().noquote()<<result.dumpToQString();

    emit signalDataParsed(result);
}


VehiclePositionResult GolemioVehiclePositions::parseMessage(QByteArray receivedMessage)
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
    /*
    gtfsTripId=mVstupniJson["gtfs_trip_id"].toString();
    routeType=mVstupniJson["route_type"].toString();
    routeShortName=mVstupniJson["route_short_name"].toString();
    originRouteName=mVstupniJson["origin_route_name"].toString();
    runNumber=mVstupniJson["run_number"].toInt();
    tripHeadsign=mVstupniJson["trip_headsign"].toString();
    //result.=mVstupniJson[""].toString();
    coordinates=geometryToQPointF(mVstupniJson["geometry"]);
    */
}

QString VehiclePositionResult::dumpToQString()
{
    QString result;
    /*
    result+="gtfs_trip_id: "+gtfsTripId+"\n";
    result+="route_type: "+routeType+"\n";
    result+="route_short_name: "+routeShortName+"\n";
    result+="origin_route_name: "+originRouteName+"\n";
    result+="run_number: "+QString::number(runNumber)+"\n";
    result+="trip_headsign: "+tripHeadsign+"\n";
    result+="geometry: "+QString::number(coordinates.x())+","+QString::number(coordinates.y())+"\n";
    */
    return result;
}
