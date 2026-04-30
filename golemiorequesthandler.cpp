#include "golemiorequesthandler.h"

GolemioRequestHandler::GolemioRequestHandler(QByteArray klic)
{
    mKlic = klic;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestReceived(QNetworkReply*)));
}


void GolemioRequestHandler::setKlic(const QByteArray &newKlic)
{
    mKlic = newKlic;
}

void GolemioRequestHandler::setParametry(const QString &newParametry)
{
    mParametry = newParametry;
}

void GolemioRequestHandler::setAdresa(const QString &newAdresa)
{
    mAdresa = newAdresa;
}


QByteArray GolemioRequestHandler::requestReceived(QNetworkReply* receivedReply)
{
    qDebug()<<Q_FUNC_INFO;
    QByteArray rawData = receivedReply->readAll();
    // QString textData(rawData);
    //  qDebug() << textData;
    qDebug().noquote()<<"kod: "<<receivedReply->error()<< "raw: "<<rawData;
    if(receivedReply->error()!=QNetworkReply::NoError)
    {
        emit signalError(receivedReply->errorString()+" "+rawData.replace("\\",""));
    }
    this->stazenaData=rawData;
    emit stazeniHotovo();
    emit signalReceivedData(rawData);
    return rawData;
}

void GolemioRequestHandler::startDataDownload(QString golemioAttributes)
{
    qDebug()<<Q_FUNC_INFO;

    QString completeAddress=mAdresa+golemioAttributes;

    qDebug()<<"golemio request address: "<<completeAddress;
    QNetworkRequest newRequest;
    newRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    newRequest.setUrl(QUrl(completeAddress));
    newRequest.setRawHeader("X-Access-Token",mKlic);

    manager->get(newRequest);
    //manager->get(QNetworkRequest(QUrl(adresa)));
}
