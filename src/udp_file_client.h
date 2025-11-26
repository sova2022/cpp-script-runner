#pragma once

#include <QByteArray>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QUdpSocket>


const quint16 PORT = 7755;

class UdpFileClient : public QObject {
    Q_OBJECT
public:
    explicit UdpFileClient(QObject* parent = nullptr)
        : QObject(parent)
        , socket_(new QUdpSocket(this)) {
        connect(socket_, &QUdpSocket::readyRead,
            this, &UdpFileClient::readPendingDatagrams);
    }

    ~UdpFileClient() override = default;

    void RequestScript(const QString& ip) {
        QByteArray req("REQ");
        socket_->writeDatagram(req, QHostAddress(ip), PORT);
    }

signals:
    void scriptReceived(const QString script);


private slots:
    void readPendingDatagrams() {
        while (socket_->hasPendingDatagrams()) {
            QNetworkDatagram datagram = socket_->receiveDatagram();
            const QString script = QString::fromUtf8(datagram.data());

            emit scriptReceived(script);
        }
    }

private:
    QUdpSocket* socket_;
};