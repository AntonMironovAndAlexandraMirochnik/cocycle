#include "NetworkConnectionServer.h"
#include "NetworkConnectionClient.h"
#include "Public/NetworkClient.h"
#include "Log.h"

const int NetworkStatusTimerInterval = 60 * 1000;

NetworkConnectionServer::NetworkConnectionServer(QObject *parent) : QTcpServer(parent) {
}

void NetworkConnectionServer::start(const QHostAddress &address, quint16 port) {
    if (!listen(address, port)) throw tr("Can't start server with error %1").arg(errorString());
    Debug(tr("Network Server started at %1 : %2").arg(serverAddress().toString()).arg(serverPort()));
    networkStatusTimer = startTimer(NetworkStatusTimerInterval);
}

void NetworkConnectionServer::stop() {
    killTimer(networkStatusTimer);
    close();
    Debug(tr("Network Server finished."));
}

void NetworkConnectionServer::timerEvent(QTimerEvent *timerEvent) {
    if (networkStatusTimer == timerEvent->timerId()) {
        checkStatus();
        timerEvent->accept();
    } else {
        QObject::timerEvent(timerEvent);
    }
}

void NetworkConnectionServer::checkStatus() {
    if (!isListening()) {
        Warning(tr("Server error: %1.").arg(errorString()));
        emit errorAppeared(errorString());
    } else {
        Info(tr("Server is OK."));
    }
}

void NetworkConnectionServer::incomingConnection(int handle) {
    NConnectionClient connectionClient = NConnectionClient(new NetworkConnectionClient(this));
    if (connectionClient->setSocketDescriptor(handle)) {
        addPendingConnection(connectionClient);
        emit newConnectionClient(connectionClient);
    } else {
        emit errorAppeared(tr("Server client error: %1.").arg(connectionClient->error()));
    }
}
