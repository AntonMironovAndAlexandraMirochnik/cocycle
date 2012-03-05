#include "MainController.h"
#include "Network.h"
#include "Ui/MainWindowController.h"
#include "Log.h"

MainController::MainController(QObject *parent) :  QObject(parent) {
    _networkThread = new NetworkThread(this);
    _mainWindowController = new MainWindowController(this);

    connect(mainWindowController(), SIGNAL(shouldQuit()), this, SLOT(stop()));
    connect(networkThread(), SIGNAL(initialized()), this, SLOT(networkThreadInitialized()));
    connect(networkThread(), SIGNAL(finished()), this, SLOT(deleteLater()));
}

MainController::~MainController() {
    QApplication::instance()->quit();
}

NetworkThread* MainController::networkThread() const { return _networkThread.data(); }

NetworkServer* MainController::networkServer() const { return _networkServer.data(); }

MainWindowController* MainController::mainWindowController() const { return _mainWindowController.data(); }

void MainController::start() {
    networkThread()->start(QThread::LowestPriority);
    mainWindowController()->showWindow();
}

void MainController::stop() {
    networkThread()->quit();
}

void MainController::networkThreadInitialized() {
    _networkServer = networkThread()->createServer(this);
    connect(mainWindowController(), SIGNAL(shouldStartServer(QString,quint16)), this, SLOT(onShouldStartServer(QString,quint16)));
    connect(mainWindowController(), SIGNAL(shouldStopServer()), networkServer(), SLOT(stopServer()));
}

void MainController::onShouldStartServer(const QString &addressString, quint16 port) {
    QHostAddress hostAddress(addressString);
    if (!hostAddress.isNull()) {
        networkServer()->startServer(hostAddress, port);
    }
}

void MainController::onClientConnected(NetworkClient* client) {
    Info("Client connected ");
}

