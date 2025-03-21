#include "AppManager.h"
#include "config.h"
#include <qtconcurrent>
#include <qthreadpool.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(Client::Name);

    AppManager stateManager;
    QObject::connect(&stateManager, &AppManager::finished, &app, &QApplication::quit);
    stateManager.start();

    return app.exec();
}
