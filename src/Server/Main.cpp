#include "Log.h"
#include "MainController/MainController.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication application(argc, argv);
    application.setApplicationName("Cocycle Server");
    application.setApplicationVersion("0.0 stage 1");
    application.setQuitOnLastWindowClosed(false);

    Info(QString("%1 started.").arg(application.applicationName()));
    LogStartSection();

    MainController *mainController = new MainController();
    QMetaObject::invokeMethod(mainController, "start", Qt::QueuedConnection);

    int applicationResult = application.exec();

    LogFinishSection();
    Info(QString("Appliction finished."));

    return applicationResult;
}
