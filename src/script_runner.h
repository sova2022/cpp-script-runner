#pragma once

#include <QtWidgets/QMainWindow>
#include <QRegularExpression>
#include <QScriptEngine>

#include "ui.h"
#include "udp_file_client.h"

/**
* Регулярное выражение для проверки корректного IPv4-адреса
* Формат IPv4: четыре числа от 0 до 255, разделённые точками, без лишних символов
* Примеры валидных адресов: 127.0.0.1, 192.168.0.255, 0.0.0.0, 255.255.255.255
* Примеры невалидных: 256.0.0.1, 192.168.1, 192.168.1.1.1, 192. 168.1.1
*/
const QRegularExpression IP_REGEX(
	R"(^((25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})\.){3}(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})$)"
);

/**
 * @brief Основной контроллер приложения Script Runner.
 *
 * Связывает:
 * - UI
 * - CanvasAPI
 * - UDP-клиент
 * - QScriptEngine
 *
 * Обрабатывает запуск скрипта, сетевые события и ошибки.
 */
class ScriptRunner : public QObject {
	Q_OBJECT
public:
	explicit ScriptRunner(QObject* parent = nullptr);	

	~ScriptRunner();

	void ConnectWidgetsSignals();
	void Show();

private slots:
	void onError(const QString& msg);
	void onRun();
	void onScriptRecieved(const QString& script);

private:
	Ui* ui_;
	CanvasAPI* canvasApi_;
	UdpFileClient* client_;
	QScriptEngine engine_;

	/**
	 * @brief Отправить сетевой запрос на получение скрипта.
	 */
	void RequestScript();
};

