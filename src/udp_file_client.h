#pragma once

#include <QByteArray>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QTimer>
#include <QUdpSocket>

const quint16 PORT = 7755;

/**
 * @brief UDP-клиент для запроса и получения Qt Script файла.
 *
 * Работает по простому протоколу:
 * - отправляет пакет "REQ" на указанный IP и порт(порт задан константно 7755)
 * - получает ответ — содержимое файла скрипта
 *
 * Генерирует сигналы:
 * - error() при сетевой ошибке
 * - scriptReceived() при успешном получении файла
 */
class UdpFileClient : public QObject {
    Q_OBJECT
public:
    explicit UdpFileClient(QObject* parent = nullptr);

    ~UdpFileClient() override = default;

    /**
     * @brief Отправить запрос на получение скрипта.
     * @param ip IP адрес сервера Script Editor.
     */
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
