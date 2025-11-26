#include "script_runner.h"

ScriptRunner::ScriptRunner(QObject* parent)
	: QObject(parent)
	, ui_(new Ui())
	, canvasApi_(new CanvasAPI(ui_->GetCanvas()))
	, client_(new UdpFileClient(this)) {
	engine_.globalObject().setProperty(
		"canvas",
		engine_.newQObject(canvasApi_)
	);
}

ScriptRunner::~ScriptRunner() {
	ui_->~Ui();
}

void ScriptRunner::ConnectWidgetsSignals() {
	connect(ui_->GetRunBtn(), &QPushButton::clicked, this, &ScriptRunner::onRun);
	connect(client_, &UdpFileClient::scriptReceived, this, &ScriptRunner::onScriptRecieved);
	connect(client_, &UdpFileClient::error, this, &ScriptRunner::onError);
}

void ScriptRunner::Show() {
	ui_->show();
}

void ScriptRunner::RequestScript() {
	client_->RequestScript(ui_->GetIpEdit()->text());
}

// slots

void ScriptRunner::onError(const QString& msg) {
	QMessageBox::critical(
		ui_,
		"Server Error",
		msg
	);
}

void ScriptRunner::onRun() {
	QString ip = ui_->GetIpEdit()->text();
	auto match = IP_REGEX.match(ip);

	if (!match.hasMatch()) {
		QMessageBox::warning(ui_, "Error", "Invalid IP address");
		return;
	}

	RequestScript();
}

void ScriptRunner::onScriptRecieved(const QString& script) {
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