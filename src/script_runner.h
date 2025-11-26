#pragma once

#include <QtWidgets/QMainWindow>
#include <QRegularExpression>

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

	}

	~ScriptRunner() override {
		ui_->~Ui();
	}

	void ConnectWidgetsSignals() {
		connect(ui_->GetRunBtn(), &QPushButton::clicked, this, &ScriptRunner::onRun);

	}

	void Show() {
		ui_->show();
	}

	void TestDraw() {
		canvasApi_->clear();
		canvasApi_->line(10, 10, 200, 10, "blue");
		canvasApi_->rect(50, 50, 100, 80, "green");
		canvasApi_->ellipse(200, 100, 60, 60, "red");
		canvasApi_->triangle(300, 300, 350, 300, 325, 250, "magenta");
	}

public slots:


private slots:
	void requestScript() {
		client_->RequestScript(ui_->GetIpEdit()->text());
	}

	void onRun() {
		qDebug() << "qq";
		QString ip = ui_->GetIpEdit()->text();
		auto match = IP_REGEX.match(ip);

		if (!match.hasMatch()) {
			QMessageBox::warning(ui_, "Error", "Invalid IP address");
			return;
		}
		requestScript();
	}


private:
	Ui* ui_;
	CanvasAPI* canvasApi_;
	UdpFileClient* client_;
};

