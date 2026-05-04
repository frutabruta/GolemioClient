#ifndef GOLEMIODEPARTUREBOARDSV2_H
#define GOLEMIODEPARTUREBOARDSV2_H

#include <QtXml>

#include "stopgolemio.h"
#include "connectiongolemio.h"
#include "golemiorequesthandler.h"

class GolemioInfotext
{


public:
    enum DisplayType
    {
        DisplayTypeInline,
        DisplayTypeGeneral,
        DisplayTypeGeneralAlternate
    };

    DisplayType display_type=DisplayTypeGeneral;
    QString text="";
    QString text_en="";
    QVector<QString> related_stops;
    QDateTime valid_from;
    QDateTime valid_to;

    static QString displayTypeToQString(GolemioInfotext::DisplayType input);
    static GolemioInfotext::DisplayType displayTypeFromQString(QString input);

};


class GolemioDepartureBoardsV2 : public GolemioRequestHandler
{
    Q_OBJECT
public:
    //konstruktor a destruktor
    GolemioDepartureBoardsV2(QByteArray apiKey);
    ~GolemioDepartureBoardsV2();

    //  QByteArray vystupData="";
    // QVector<PrestupMPV> seznamPrestupuMpv;
    QVector<ConnectionGolemio> connectionGolemioList;
    QVector<StopGolemio> stopGolemioList;
    QVector<GolemioInfotext> golemioInfotextList;

    void fillJsonFromQByteArray();
    void fillJsonFromQByteArray(QByteArray inputData);
    void startDataDownload(int cisloCis);
    using GolemioRequestHandler::startDataDownload;
    //QVector<ConnectionMPV> vyfiltrujPrestupy(QVector<ConnectionMPV> vstupniPrestupy, Line linka); //unused
    //  bool jePrestupNaSeznamu(ConnectionMPV prestup, QVector<ConnectionMPV> seznamPrestupu);

    QVector<GolemioInfotext> parseDomDocumentInfotexts();
    QVector<ConnectionGolemio> parseDomDocumentDepartures();
    QVector<StopGolemio> parseDomDocumentStops();

    // QVector<ConnectionGolemio> parsujDomDokument();



protected:
    //instance


    //promenne

    QJsonDocument mDataJson;
};

#endif // GOLEMIODEPARTUREBOARDSV2_H
