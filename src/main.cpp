#include "script_runner.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    ScriptRunner sr;
    sr.Show();

    sr.TestDraw();
    return app.exec();
}
