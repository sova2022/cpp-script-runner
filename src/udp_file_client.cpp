#include "udp_file_client.h"

UdpFileClient::UdpFileClient(QObject* parent)
    : QObject(parent)
    , socket_(new QUdpSocket(this)) {
    connect(socket_, &QUdpSocket::readyRead, 
        this, &UdpFileClient::readPendingDatagrams);
}

void UdpFileClient::RequestScript(const QString& ip) {
    received_ = false;

    QByteArray req("REQ");
    socket_->writeDatagram(req, QHostAddress(ip), PORT);
    QTimer::singleShot(1000, this, [this]() {
        if (!received_) {
            emit error("No response from server (timeout)");
        }
        });
}

void UdpFileClient::readPendingDatagrams() {
    while (socket_->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket_->receiveDatagram();
        QByteArray data = datagram.data();
        
        if (data.isEmpty()) {
            emit error("Received empty script");
            continue;
        }

        QString script = QString::fromUtf8(data);
        if (script.isEmpty()) {
            emit error("Received invalid UTF-8 script");
            continue;
        }
        received_ = true;
        emit scriptReceived(script);
    }
}

