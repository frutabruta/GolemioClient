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

    void setKlic(const QByteArray &newKlic);
    void setParametry(const QString &newParametry);
    void setAdresa(const QString &newAdresa);

    void startDataDownload(QString golemioAttributes);

protected:
    QByteArray stazenaData="";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QByteArray mKlic="";
    QString mAdresa="http://api.golemio.cz/v2/pid/departureboards/";
    QString mParametry="";

protected slots:
    QByteArray requestReceived(QNetworkReply *receivedReply);

signals:
    void stazeniHotovo ();
    void signalError(QString errorMessage);
    void signalReceivedData(QByteArray receivedMessage);
};

#endif // GOLEMIOREQUESTHANDLER_H
