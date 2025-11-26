#pragma once

#include <QByteArray>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QTimer>
#include <QUdpSocket>

const quint16 PORT = 7755;

class UdpFileClient : public QObject {
    Q_OBJECT
public:
    explicit UdpFileClient(QObject* parent = nullptr);

    ~UdpFileClient() override = default;

    void RequestScript(const QString& ip);

signals:
    void error(const QString& msg);
    void scriptReceived(const QString& script);

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket* socket_;
    bool received_ = false;
};