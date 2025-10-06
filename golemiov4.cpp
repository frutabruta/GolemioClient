#include "golemiov4.h"

GolemioV4::GolemioV4(const QByteArray key) : Golemio(key)
{

}

QVector<ConnectionGolemioV4> GolemioV4::parseDomDocumentDepartures()
{
    qDebug()<<Q_FUNC_INFO;

    //   qDebug()<<"vstup:"<<vstupniJson["departures"];
    seznamPrestupuGolemio.clear();

    if(!mVstupniJson["departures"].isArray())
    {
        return seznamPrestupuGolemio;
    }
    QJsonArray odjezdy=mVstupniJson["departures"].toArray();

    if(odjezdy.isEmpty())
    {
        return seznamPrestupuGolemio;
    }



    foreach (QJsonValue var, odjezdy) {


        //var[""][""]

        ConnectionGolemioV4 novy;
        /* novy.arrivalTimestampPredicted=ConnectionGolemio::qStringDoQDateTime(var["arrival_timestamp"]["predicted"].toString());
        novy.arrivalTimestampScheduled=ConnectionGolemio::qStringDoQDateTime(var["arrival_timestamp"]["scheduled"].toString());
        novy.arrivalTimestampMinutes=var["arrival_timestamp"]["minutes"].toString();

        if(var.toObject().contains("delay") )
        {
            novy.delayIsAvailable=var["delay"]["is_available"].toBool();
            novy.delayMinutes=var["delay"]["minutes"].toInt();
            novy.delaySeconds=var["delay"]["seconds"].toInt();
        }
*/

        QJsonArray minutesArray=var["departure_timestamp"]["minutes"].toArray();
        foreach(QJsonValue selectedObject, minutesArray)
        {
            novy.departureTimestampMinutes<<selectedObject.toString();
        }
        novy.departureTimestampPredicted=ConnectionGolemio::qStringDoQDateTime(var["departure_timestamp"]["predicted"].toString());
        novy.departureTimestampScheduled=ConnectionGolemio::qStringDoQDateTime(var["departure_timestamp"]["scheduled"].toString());



        //last stop


        //  novy.lastStopName=(var["last_stop"]["name"].toString());
        //   novy.lastStopName=(var["last_stop"]["id"].toString());

        if(var.toObject().contains("route") )
        {
            novy.routeShortName=var["route"]["short_name"].toString();
            novy.routeType=var["route"]["type"].toInt();
            //    novy.routeIsNight=var["route"]["is_night"].toBool();
            //    novy.routeIsRegional=var["route"]["is_regional"].toBool();
            //    novy.routeIsSubstituteTransport=var["route"]["is_substitute_transport"].toBool();
        }


        if(var.toObject().contains("stop") )
        {
           // novy.stopId=var["stop"]["id"].toString();
            novy.stopPlatformCode=var["stop"]["platform_code"].toString();
        }




        if(var.toObject().contains("trip") )
        {
          //  novy.tripDirection=var["trip"]["direction"].toString();
            novy.tripHeadsign=var["trip"]["headsign"].toString();
            novy.tripId=var["trip"]["id"].toString();
           // novy.tripIsAtStop=var["trip"]["is_at_stop"].toBool();
           // novy.tripIsCanceled=var["trip"]["is_canceled"].toBool();
            novy.tripIsWheelchairAccessible=var["trip"]["is_wheelchair_accessible"].toBool();
          //  novy.tripIsAirConditioned=var["trip"]["is_air_conditioned"].toBool();
          //  novy.tripShortName=var["trip"]["short_name"].toString();
        }

        //     novy.t=nodes.at(i).attributes().namedItem("t").nodeValue();

        novy.substitutionTextCs=var["substitution_text"]["cs"].toString();
        novy.substitutionTextEn=var["substitution_text"]["en"].toString();


        qDebug().noquote()<<"odjezd: "<<novy.routeShortName<<"\t"<<novy.tripHeadsign<<"\t["<<novy.stopPlatformCode<<"]\t"<<novy.departureTimestampMinutes.join(",");

        seznamPrestupuGolemio.append(novy);

    }




    return seznamPrestupuGolemio;
}
