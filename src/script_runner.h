#pragma once

#include <QtWidgets/QMainWindow>

#include "ui.h"

class ScriptRunner : public QObject {
	Q_OBJECT
public:
	explicit ScriptRunner(QObject* parent = nullptr)
		: QObject(parent)
		, ui_(new Ui()) {

	}

	~ScriptRunner() override {
		ui_->~Ui();
	}

	void ConnectWidgetsSignals() {

	}

	void Show() {
		ui_->show();
	}

	void TestDraw() {
		auto canvas = ui_->GetCanvas();
		canvas->Clear();
		canvas->AddLine(10, 10, 200, 10, "blue");
	}

public slots:


private slots:


private:
	Ui* ui_;

};

