#include "golemiodepartureboardsv2.h"
#include "connectiongolemio.h"

//FROM QtBDF
/*
 * Instalace https://

1. Install OpenSSL from Maintenance Tool.

62270ee4-db0f-4054-903f-bc925d6f3afe-image.png

2. Independently of your compiler, go to C:\Qt\Tools\OpenSSL\Win_x64\bin (if you have 64 bits application).

3. Copy libcrypto-1_1-x64.dll and libssl-1_1-x64.dll and paste in your release or debug application executable.

https://forum.qt.io/topic/127049/connecttohostencrypted-tls-initialization-failed/6
*/

Q_LOGGING_CATEGORY(GolemioDepartureBoardsV2Log, "GolemioDepartureBoardsV2")

GolemioDepartureBoardsV2::GolemioDepartureBoardsV2(QByteArray apiKey): GolemioRequestHandler(apiKey)
{
    mAddress="http://api.golemio.cz/v2/pid/departureboards/";
    //adresa+="&minutesBefore=10"
    mParameters+="&minutesAfter=120";
    //adresa+= "&timeFrom=2021-01-21T06%3A00%3A00"
    mParameters+="&includeMetroTrains=true";
    //adresa+= "&preferredTimezone=Europe%252FPrague"
    mParameters+="&mode=departures";
    mParameters+="&order=real";
    mParameters+="&filter=routeHeadingOnce";
    mParameters+="&skip=canceled";
    mParameters+="&limit=10";
    //adresa+="&total=0"
    //adresa+= "&offset=0";

}
GolemioDepartureBoardsV2::~GolemioDepartureBoardsV2()
{
}

void GolemioDepartureBoardsV2::fillJsonFromQByteArray()
{
    qCDebug(GolemioDepartureBoardsV2Log)<<Q_FUNC_INFO;
    fillJsonFromQByteArray(downloadedData);
}

void GolemioDepartureBoardsV2::fillJsonFromQByteArray(QByteArray inputData)
{
    qCDebug(GolemioDepartureBoardsV2Log)<<Q_FUNC_INFO;
    mDataJson=mDataJson.fromJson(inputData);
}

QVector<ConnectionGolemio> GolemioDepartureBoardsV2::parseDomDocumentDepartures()
{
    qCDebug(GolemioDepartureBoardsV2Log)<<Q_FUNC_INFO;

    //   qCDebug(GolemioDepartureBoardsV2Log)<<"vstup:"<<vstupniJson["departures"];
    connectionGolemioList.clear();

    if(!mDataJson["departures"].isArray())
    {
        return connectionGolemioList;
    }
    QJsonArray departuresArray=mDataJson["departures"].toArray();

    if(departuresArray.isEmpty())
    {
        return connectionGolemioList;
    }

    foreach (QJsonValue var, departuresArray)
    {
        ConnectionGolemio connectionGolemio;
        connectionGolemio.arrivalTimestampPredicted=ConnectionGolemio::qStringDoQDateTime(var["arrival_timestamp"]["predicted"].toString());
        connectionGolemio.arrivalTimestampScheduled=ConnectionGolemio::qStringDoQDateTime(var["arrival_timestamp"]["scheduled"].toString());
        connectionGolemio.arrivalTimestampMinutes=var["arrival_timestamp"]["minutes"].toString();

        if(var.toObject().contains("delay") )
        {
            connectionGolemio.delayIsAvailable=var["delay"]["is_available"].toBool();
            connectionGolemio.delayMinutes=var["delay"]["minutes"].toInt();
            connectionGolemio.delaySeconds=var["delay"]["seconds"].toInt();
        }

        connectionGolemio.departureTimestampPredicted=ConnectionGolemio::qStringDoQDateTime(var["departure_timestamp"]["predicted"].toString());
        connectionGolemio.departureTimestampScheduled=ConnectionGolemio::qStringDoQDateTime(var["departure_timestamp"]["scheduled"].toString());
        connectionGolemio.departureTimestampMinutes=var["departure_timestamp"]["minutes"].toString();

        //last stop

        connectionGolemio.lastStopName=(var["last_stop"]["name"].toString());
        connectionGolemio.lastStopName=(var["last_stop"]["id"].toString());

        if(var.toObject().contains("route") )
        {
            connectionGolemio.routeShortName=var["route"]["short_name"].toString();
            connectionGolemio.routeType=var["route"]["type"].toInt();
            connectionGolemio.routeIsNight=var["route"]["is_night"].toBool();
            connectionGolemio.routeIsRegional=var["route"]["is_regional"].toBool();
            connectionGolemio.routeIsSubstituteTransport=var["route"]["is_substitute_transport"].toBool();
        }

        if(var.toObject().contains("stop") )
        {
            connectionGolemio.stopId=var["stop"]["id"].toString();
            connectionGolemio.stopPlatformCode=var["stop"]["platform_code"].toString();
        }

        if(var.toObject().contains("trip") )
        {
            connectionGolemio.tripDirection=var["trip"]["direction"].toString();
            connectionGolemio.tripHeadsign=var["trip"]["headsign"].toString();
            connectionGolemio.tripId=var["trip"]["id"].toString();
            connectionGolemio.tripIsAtStop=var["trip"]["is_at_stop"].toBool();
            connectionGolemio.tripIsCanceled=var["trip"]["is_canceled"].toBool();
            connectionGolemio.tripIsWheelchairAccessible=var["trip"]["is_wheelchair_accessible"].toBool();
            connectionGolemio.tripIsAirConditioned=var["trip"]["is_air_conditioned"].toBool();
            connectionGolemio.tripShortName=var["trip"]["short_name"].toString();
        }
        qCDebug(GolemioDepartureBoardsV2Log).noquote()<<connectionGolemio.dumpToQStringLine();
        connectionGolemioList.append(connectionGolemio);
    }

    return connectionGolemioList;
}


QVector<GolemioInfotext> GolemioDepartureBoardsV2::parseDomDocumentInfotexts()
{
    qCDebug(GolemioDepartureBoardsV2Log)<<Q_FUNC_INFO;

    //   qCDebug(GolemioDepartureBoardsV2Log)<<"vstup:"<<vstupniJson["departures"];
    golemioInfotextList.clear();

    if(!mDataJson["infotexts"].isArray())
    {
        return golemioInfotextList;
    }
    QJsonArray infotextArray=mDataJson["infotexts"].toArray();

    if(infotextArray.isEmpty())
    {
        return golemioInfotextList;
    }

    foreach (QJsonValue var, infotextArray)
    {
        GolemioInfotext golemioInfotext;

        golemioInfotext.text = var["text"].toString();
        golemioInfotext.text_en = var["text_en"].toString();
        golemioInfotext.valid_from = ConnectionGolemio::qStringDoQDateTime(var["valid_from"].toString());
        golemioInfotext.valid_to = ConnectionGolemio::qStringDoQDateTime(var["valid_to"].toString());
        golemioInfotext.display_type = golemioInfotext.displayTypeFromQString(var["display_type"].toString());

        QJsonArray relatedStopsArray = var["related_stops"].toArray();

        foreach (QJsonValue relatedStop, relatedStopsArray )
        {
            golemioInfotext.related_stops.append(relatedStop.toString());
        }

        golemioInfotextList.append(golemioInfotext);
    }

    return golemioInfotextList;
}


QVector<StopGolemio> GolemioDepartureBoardsV2::parseDomDocumentStops()
{
    qCDebug(GolemioDepartureBoardsV2Log)<<Q_FUNC_INFO;

    //   qCDebug(GolemioDepartureBoardsV2Log)<<"vstup:"<<vstupniJson["departures"];

    QVector<StopGolemio> stopGolemioList;

    QJsonArray stopArray=mDataJson["stops"].toArray();

    stopGolemioList.clear();

    foreach(QJsonValue var, stopArray)
    {
        StopGolemio stopGolemio;

        if(var.toObject().contains("platform_code") )
        {
            stopGolemio.platformName=var["platform_code"].toString();
        }

        if(var.toObject().contains("stop_name") )
        {
            stopGolemio.stopName=var["stop_name"].toString();
        }
        stopGolemioList<<stopGolemio;


    }

    return stopGolemioList;
}


// zdroj https://stackoverflow.com/questions/7218851/making-an-http-get-under-qt

void GolemioDepartureBoardsV2::startDataDownload(int cisId)
{
    qCDebug(GolemioDepartureBoardsV2Log)<<Q_FUNC_INFO;

    // QString adresa = "http://www.mpvnet.cz/"+Ids+"/x/"+QString::number(cisloCis)+"?unite=true&ko=12702&pocet=24&t=true";

    if(cisId>0)
    {
        QString address=mAddress;
        address+="?cisIds="+QString::number(cisId);
        address+=mParameters;

        qCDebug(GolemioDepartureBoardsV2Log)<<"golemio adresa dotazu: "<<address;
        QNetworkRequest newRequest;
        newRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());

        newRequest.setUrl(QUrl(address));
        newRequest.setRawHeader("X-Access-Token",mKey);

        manager.get(newRequest);
    }
    else
    {
        qCDebug(GolemioDepartureBoardsV2Log)<<"invalid cis number";
    }
}





/*
QVector<ConnectionMPV> Golemio::vyfiltrujPrestupy(QVector<ConnectionMPV> vstupniPrestupy, Line linka)
{
    qCDebug(GolemioDepartureBoardsV2Log)<<Q_FUNC_INFO;
    QVector<ConnectionMPV> vyfiltrovanePrestupy;

    foreach(ConnectionMPV aktualniPrestup, vstupniPrestupy)
    {
        if(aktualniPrestup.alias!=linka.lineName)
        {
            if(!jePrestupNaSeznamu(aktualniPrestup,vyfiltrovanePrestupy))
            {
                vyfiltrovanePrestupy.push_back(aktualniPrestup);
            }
        }
    }
    return vyfiltrovanePrestupy;
}


bool Golemio::jePrestupNaSeznamu(ConnectionMPV prestup, QVector<ConnectionMPV> seznamPrestupu)
{
    qCDebug(GolemioDepartureBoardsV2Log)<<Q_FUNC_INFO;


    foreach(ConnectionMPV testPrestup, seznamPrestupu)
    {
        if(testPrestup.alias==prestup.alias)
        {
            if(testPrestup.smer_c==prestup.smer_c)
            {
                return true;
            }
        }
    }
    return false;

}

*/



GolemioInfotext::DisplayType  GolemioInfotext::displayTypeFromQString(QString input)
{
    if(input=="general")
    {
        return GolemioInfotext::DisplayTypeGeneral;
    }
    else if(input=="general-alternate")
    {
        return GolemioInfotext::DisplayTypeGeneralAlternate;
    }
    else if(input=="inline")
    {
        return GolemioInfotext::DisplayTypeInline;
    }

    return GolemioInfotext::DisplayTypeGeneral;
}

QString GolemioInfotext::displayTypeToQString(GolemioInfotext::DisplayType input)
{
    switch (input) {
    case GolemioInfotext::DisplayTypeGeneral:
        return "general";

        break;
    case GolemioInfotext::DisplayTypeInline:
        return "inline";
        break;
    case GolemioInfotext::DisplayTypeGeneralAlternate:
        return "general-alternate";
        break;
    default:
        return "";
        break;
    }
}



