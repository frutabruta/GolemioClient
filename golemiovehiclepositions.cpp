#include "golemiovehiclepositions.h"
#include <QJsonArray>

GolemioVehiclePositions::GolemioVehiclePositions(QByteArray klic) : GolemioRequestHandler(klic)
{
    mAddress="https://api.golemio.cz/v2/vehiclepositions/";

    connect(this,&GolemioRequestHandler::signalReceivedData,this,&GolemioVehiclePositions::slotMessageReceived);
}


void GolemioVehiclePositions::slotMessageReceived(QByteArray message)
{
    QVector<VehiclePositionResult> result=parseMessage(message);


    qDebug().noquote()<<result.first().dumpToQString();

    emit signalDataParsed(result.first());
}


QVector<VehiclePositionResult> GolemioVehiclePositions::parseMessage(QByteArray receivedMessage)
{
    QVector<VehiclePositionResult> resultList;

    QJsonDocument mVstupniJson=QJsonDocument::fromJson(receivedMessage);
    QJsonObject root = mVstupniJson.object();

    QJsonArray featuresArray = root["features"].toArray();

    foreach (QJsonValue selectedObject, featuresArray)
    {
        VehiclePositionResult result(selectedObject.toObject());
        resultList<<result;
    }


    return resultList;
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

VehiclePositionResult::VehiclePositionResult(QJsonObject mVstupniJson)
{
    QJsonValue properties=mVstupniJson["properties"];

    QJsonValue trip=properties["trip"];

    QJsonValue lastPosition=properties["last_position"];

    gtfsTripId=trip["gtfs"]["trip_id"].toString();
    tripGtfsRouteType=trip["gtfs"]["route_type"].toInt();

    statePosition=lastPosition["state_position"].toString();
    lastStopGtfsId=lastPosition["last_stop"]["id"].toString();
    /*
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

    result+="gtfs_trip_id: "+gtfsTripId+"\n";

    result+="state postition:: "+statePosition+"\n";

    result+="route_type: "+QString::number(tripGtfsRouteType)+"\n";
    result+="last stop id: "+lastStopGtfsId+"\n";

    QString tripGtfsRouteType="";

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
