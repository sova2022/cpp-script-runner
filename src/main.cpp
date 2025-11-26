#include "script_runner.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    qRegisterMetaType<QPolygonF>("QPolygonF");

    QApplication app(argc, argv);
        
    ScriptRunner sr;
    sr.Show();
    sr.ConnectWidgetsSignals();

    return app.exec();
}
