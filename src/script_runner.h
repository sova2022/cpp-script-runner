#pragma once

#include <QtWidgets/QMainWindow>
#include <QRegularExpression>
#include <QScriptEngine>

#include "ui.h"
#include "udp_file_client.h"

const QRegularExpression IP_REGEX(
	R"(^((25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})\.){3}(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})$)"
);

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

	void RequestScript();
};

