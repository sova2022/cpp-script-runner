#pragma once

#include <QtWidgets/QMainWindow>

#include "ui.h"

class ScriptRunner : public QObject {
	Q_OBJECT
public:
	explicit ScriptRunner(QObject* parent = nullptr)
		: QObject(parent)
		, ui_(new Ui())
		, canvasApi_(new CanvasAPI(ui_->GetCanvas())){

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
		canvasApi_->clear();
		canvasApi_->line(10, 10, 200, 10, "blue");
		canvasApi_->rect(50, 50, 100, 80, "green");
		canvasApi_->ellipse(200, 100, 60, 60, "red");
		canvasApi_->triangle(300, 300, 350, 300, 325, 250, "magenta");
	}

public slots:


private slots:


private:
	Ui* ui_;
	CanvasAPI* canvasApi_;
};

