#ifndef GOLEMIOREQUESTHANDLER_H
#define GOLEMIOREQUESTHANDLER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>


class GolemioRequestHandler : public QObject
{
    Q_OBJECT
public:
    GolemioRequestHandler(QByteArray klic);

    void startDataDownload(QString golemioAttributes);

    void setAddress(const QString &newAddress);
    void setParameters(const QString &newParameters);
    void setKey(const QByteArray &newKey);

protected:
    QByteArray downloadedData="";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QByteArray mKey="";
    QString mAddress="http://api.golemio.cz/v2/pid/departureboards/";
    QString mParameters="";

protected slots:
    QByteArray requestReceived(QNetworkReply *receivedReply);

signals:
    void stazeniHotovo ();
    void signalError(QString errorMessage);
    void signalReceivedData(QByteArray receivedMessage);
};

#endif // GOLEMIOREQUESTHANDLER_H
