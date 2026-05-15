#include "golemiorequesthandler.h"

Q_LOGGING_CATEGORY(GolemioRequestHandlerLog, "GolemioRequestHandler")

GolemioRequestHandler::GolemioRequestHandler(QByteArray klic)
{
    mKey = klic;
    connect(&manager,&QNetworkAccessManager::finished,this,&GolemioRequestHandler::requestReceived);
}


QByteArray GolemioRequestHandler::requestReceived(QNetworkReply* receivedReply)
{
    qCDebug(GolemioRequestHandlerLog)<<Q_FUNC_INFO;
    QByteArray rawData = receivedReply->readAll();
    // QString textData(rawData);
    //  qCDebug(GolemioRequestHandlerLog) << textData;
    qCDebug(GolemioRequestHandlerLog).noquote()<<"kod: "<<receivedReply->error()<< "raw: "<<rawData;
    if(receivedReply->error()!=QNetworkReply::NoError)
    {
        emit signalError(receivedReply->errorString()+" "+rawData.replace("\\",""));
    }
    this->downloadedData=rawData;
    emit stazeniHotovo();
    emit signalReceivedData(rawData);
    return rawData;
}

void GolemioRequestHandler::startDataDownload(QString golemioAttributes)
{
    qCDebug(GolemioRequestHandlerLog)<<Q_FUNC_INFO;

    QString completeAddress=mAddress+golemioAttributes;

    qCDebug(GolemioRequestHandlerLog)<<"golemio request address: "<<completeAddress;
    QNetworkRequest newRequest;
    newRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    newRequest.setUrl(QUrl(completeAddress));
    newRequest.setRawHeader("X-Access-Token",mKey);

    manager.get(newRequest);
    //manager->get(QNetworkRequest(QUrl(adresa)));
}

void GolemioRequestHandler::setParameters(const QString &newParameters)
{
    mParameters = newParameters;
}

void GolemioRequestHandler::setAddress(const QString &newAddress)
{
    mAddress = newAddress;
}

void GolemioRequestHandler::setKey(const QByteArray &newKey)
{
    mKey = newKey;
}
