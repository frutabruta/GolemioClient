#ifndef GOLEMIO_H
#define GOLEMIO_H

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


class Golemio : public GolemioRequestHandler
{
    Q_OBJECT
public:
    //konstruktor a destruktor
    Golemio(QByteArray klic);
    ~Golemio();

    //  QByteArray vystupData="";
    // QVector<PrestupMPV> seznamPrestupuMpv;
    QVector<ConnectionGolemio> seznamPrestupuGolemio;
    QVector<StopGolemio> stopGolemioList;
    QVector<GolemioInfotext> golemioInfotextList;

    void naplnVstupDokument(QByteArray vstup);
    void startDataDownload(int cisloCis);
    //QVector<ConnectionMPV> vyfiltrujPrestupy(QVector<ConnectionMPV> vstupniPrestupy, Line linka); //unused
    //  bool jePrestupNaSeznamu(ConnectionMPV prestup, QVector<ConnectionMPV> seznamPrestupu);

    QVector<GolemioInfotext> parseDomDocumentInfotexts();
    QVector<ConnectionGolemio> parseDomDocumentDepartures();
    QVector<StopGolemio> parseDomDocumentStops();

    // QVector<ConnectionGolemio> parsujDomDokument();


protected:
    //instance


    //promenne

    QJsonDocument mVstupniJson;
};

#endif // GOLEMIO_H
