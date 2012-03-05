#include "Application.h"
#include "Log.h"
#include "MainController/MainController.h"

Application::Application(int argc, char** argv) : QApplication(argc, argv) {
    setApplicationName("Cocycle Client");
    setApplicationVersion("0.0 stage 1");
    setQuitOnLastWindowClosed(false);
}

int Application::exec() {
    Info(tr("%1 started.").arg(applicationName()));
    LogStartSection();

    _mainController = new MainController();
    QMetaObject::invokeMethod(mainController(), "start", Qt::QueuedConnection);

    int applicationResult = QApplication::exec();

    LogFinishSection();
    Info(tr("Appliction finished."));

    return applicationResult;
}


MainController* Application::mainController() const {
    return _mainController;
}
