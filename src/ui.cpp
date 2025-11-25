#include "ui.h"

Ui::Ui(QWidget* parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags) {
    SetUi();
}

CanvasWidget* Ui::GetCanvas() {
    return canvas_; 
}
QLineEdit* Ui::GetIpEdit() {
    return ipEdit_; 
}
QPushButton* Ui::GetRunBtn() {
    return runBtn_; 
}

void Ui::SetCurrentStatusInStatusBar(const QString& msg) {
    statusBar()->showMessage(msg);
}

void Ui::SetUi() {
    setWindowTitle(QString("%1 %2").arg(NAME_PROGRAMM, VERSION));
    setMinimumSize(QSize{ 640, 480 });
    setWindowIcon(QIcon(":/images/img/icon.ico"));

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    canvas_ = new CanvasWidget(centralWidget);
    canvas_->setStyleSheet("background: white; border: 1px solid #ccc;");
    mainLayout->addWidget(canvas_, 1);

    QWidget* panel = new QWidget(centralWidget);
    panel->setFixedWidth(120);
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);

    QLabel* ipLabel = new QLabel("Editor IP:", panel);
    panelLayout->addWidget(ipLabel);

    ipEdit_ = new QLineEdit(panel);
    ipEdit_->setPlaceholderText("127.0.0.1");
    panelLayout->addWidget(ipEdit_);

    runBtn_ = new QPushButton("Run", panel);
    runBtn_->setMinimumHeight(40);
    panelLayout->addWidget(runBtn_);

    panelLayout->addStretch();
    mainLayout->addWidget(panel);

    SetCurrentStatusInStatusBar("Ready");
}



// ====== ÏÀÍÅËÜ ÑÏĞÀÂÀ ======
