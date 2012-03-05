#include "MainController.h"
#include "Network.h"
#include "Ui/MainWindowController.h"
#include "Ui/LoginDialogController.h"

MainController::MainController(QObject *parent) :  QObject(parent) {
    _networkThread = new NetworkThread(this);

    connect(networkThread(), SIGNAL(initialized()), this, SLOT(networkThreadInitialized()));
    connect(networkThread(), SIGNAL(finished()), this, SLOT(deleteLater()));

}

MainController::~MainController() {
    QApplication::instance()->quit();
}

NetworkThread* MainController::networkThread() const { return _networkThread.data(); }

NetworkClient* MainController::networkClient() const { return _networkClient.data(); }

MainWindowController* MainController::mainWindowController() const { return _mainWindowController.data(); }

LoginDialogController* MainController::loginDialogController() const { return _loginDialogController.data(); }

void MainController::initMainWindowController() {
    _mainWindowController = new MainWindowController(this);
    connect(mainWindowController(), SIGNAL(shouldQuit()), this, SLOT(stop()));
}

void MainController::initLoginDialogController() {
    _loginDialogController = new LoginDialogController(networkClient(), this);
    connect(loginDialogController(), SIGNAL(accepted()), this, SLOT(loginDialogAccepted()));
    connect(loginDialogController(), SIGNAL(rejected()), this, SLOT(loginDialogRejected()));
}

void MainController::start() {
    networkThread()->start(QThread::LowestPriority);
//    mainWindowController()->showWindow();
}

void MainController::stop() {
    networkThread()->quit();
}

void MainController::networkThreadInitialized() {
    _networkClient = networkThread()->createClient(this);

    initLoginDialogController();
    loginDialogController()->open();
}

void MainController::loginDialogAccepted() {
    initMainWindowController();
    mainWindowController()->window()->show();
}

void MainController::loginDialogRejected() {
    stop();
}
