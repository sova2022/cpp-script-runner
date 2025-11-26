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
	explicit ScriptRunner(QObject* parent = nullptr)
		: QObject(parent)
		, ui_(new Ui())
		, canvasApi_(new CanvasAPI(ui_->GetCanvas()))
		, client_(new UdpFileClient(this)) {
		engine_.globalObject().setProperty(
			"canvas",
			engine_.newQObject(canvasApi_)
		);
	}

	~ScriptRunner() override {
		ui_->~Ui();
	}

	void ConnectWidgetsSignals() {
		connect(ui_->GetRunBtn(), &QPushButton::clicked, this, &ScriptRunner::onRun);
		connect(client_, &UdpFileClient::scriptReceived, this, &ScriptRunner::onScriptRecieved);
	}

	void Show() {
		ui_->show();
	}

public slots:


private slots:
	void requestScript() {
		client_->RequestScript(ui_->GetIpEdit()->text());
	}

	void onRun() {
		QString ip = ui_->GetIpEdit()->text();
		auto match = IP_REGEX.match(ip);

		if (!match.hasMatch()) {
			QMessageBox::warning(ui_, "Error", "Invalid IP address");
			return;
		}
		requestScript();
	}

	void onScriptRecieved(const QString script) {
		QScriptValue result = engine_.evaluate(script);
		if (engine_.hasUncaughtException()) {
			int line = engine_.uncaughtExceptionLineNumber();
			QString message = result.toString();

			QMessageBox::critical(
				ui_,
				"Script Error",
				QString("Error at line %1:\n%2").arg(line).arg(message)
			);

			return;
		}
	}


private:
	Ui* ui_;
	CanvasAPI* canvasApi_;
	UdpFileClient* client_;
	QScriptEngine engine_;
};

