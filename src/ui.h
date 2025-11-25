#pragma once

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QStatusBar>
#include <QVBoxLayout>

#include "canvas.h"

const QString NAME_PROGRAMM = "Script Runner";
const QString VERSION = "ver. 1.0.0";

class Ui : public QMainWindow {
    Q_OBJECT
public:
    explicit Ui(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    ~Ui() override = default;

    CanvasWidget* GetCanvas();
    QLineEdit* GetIpEdit();
    QPushButton* GetRunBtn();
    void SetCurrentStatusInStatusBar(const QString& msg);

private:
    CanvasWidget* canvas_;
    QLineEdit* ipEdit_;
    QPushButton* runBtn_;

    void SetUi();
};

