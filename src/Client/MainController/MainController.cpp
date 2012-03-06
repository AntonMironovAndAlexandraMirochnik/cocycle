#include "MainController.h"
#include "Network.h"
#include "MainWindow/MainWindowController.h"
#include "Login/LoginDialogController.h"

MainController::MainController(QObject *parent) :  QObject(parent) {
    initNetworkThread();
    initMainWindowController();
    initLoginDialogController();
}

MainController::~MainController() {
    QCoreApplication::instance()->quit();
}

NetworkClient* MainController::networkClient() const { return _networkClient.data(); }

void MainController::initNetworkClient() {
    _networkClient = networkThread()->createClient(this);
    connect(networkClient(), SIGNAL(started()), this, SLOT(onNetworkClientStarted()));

    loginDialogController()->setNetworkClient(networkClient());
}

NetworkThread* MainController::networkThread() const { return _networkThread.data(); }

void MainController::initNetworkThread() {
    _networkThread = new NetworkThread(this);

    connect(networkThread(), SIGNAL(initialized()), this, SLOT(onNetworkThreadInitialized()));
    connect(networkThread(), SIGNAL(finished()), this, SLOT(deleteLater()));
}

MainWindowController* MainController::mainWindowController() const { return _mainWindowController.data(); }

void MainController::initMainWindowController() {
    _mainWindowController = new MainWindowController(this);
    connect(mainWindowController(), SIGNAL(shouldQuit()), this, SLOT(stop()));
}

LoginDialogController* MainController::loginDialogController() const { return _loginDialogController.data(); }

void MainController::initLoginDialogController() {
    _loginDialogController = new LoginDialogController(this);
}

void MainController::start() {
    networkThread()->start(QThread::LowestPriority);
}

void MainController::stop() {
    delete loginDialogController();
    networkThread()->quit();
}

void MainController::onNetworkThreadInitialized() {
    initNetworkClient();
}

void MainController::onNetworkClientStarted() {
    mainWindowController()->showWindow();
}
