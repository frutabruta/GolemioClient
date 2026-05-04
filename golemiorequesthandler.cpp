#include "golemiorequesthandler.h"

GolemioRequestHandler::GolemioRequestHandler(QByteArray klic)
{
    mKey = klic;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestReceived(QNetworkReply*)));
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
    this->downloadedData=rawData;
    emit stazeniHotovo();
    emit signalReceivedData(rawData);
    return rawData;
}

void GolemioRequestHandler::startDataDownload(QString golemioAttributes)
{
    qDebug()<<Q_FUNC_INFO;

    QString completeAddress=mAddress+golemioAttributes;

    qDebug()<<"golemio request address: "<<completeAddress;
    QNetworkRequest newRequest;
    newRequest.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    newRequest.setUrl(QUrl(completeAddress));
    newRequest.setRawHeader("X-Access-Token",mKey);

    manager->get(newRequest);
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
