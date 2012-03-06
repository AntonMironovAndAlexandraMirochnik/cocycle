#include "NetworkServer.h"
#include "NetworkClient.h"
#include "Private/NetworkConnectionServer.h"

const QString NetworkServer::VerificationString("I am the king.");

NetworkServer::NetworkServer(QObject *parent) : QObject(parent) {
    _lastClientId = 0;
    connect(this, SIGNAL(clientConnected(NClient)), this, SLOT(onClientConnected(NClient)));
}

NConnectionServer NetworkServer::connectionServer() const {
    return _connectionServer;
}

void NetworkServer::setConnectionServer(NConnectionServer connectionServer) {
    _connectionServer = connectionServer;
    connect(connectionServer.data(), SIGNAL(newConnectionClient(NConnectionClient)), this, SLOT(onConnectionClientConnected(NConnectionClient)));
    emit initialized();
}

void NetworkServer::startServer(const QHostAddress &address, quint16 port) {
    QMetaObject::invokeMethod(connectionServer(), "start", Q_ARG(QHostAddress, address), Q_ARG(quint16, port));
}

void NetworkServer::stopServer() {
    QMetaObject::invokeMethod(connectionServer(), "stop");
}

void NetworkServer::onConnectionClientConnected(NConnectionClient connectionClient) {
    ++_lastClientId;
    NClient client = new NetworkClient(this, _lastClientId);
    _clients[_lastClientId] = client;
    client->setConnectionClient(connectionClient);
    connect(client.data(), SIGNAL(verified(bool)), this, SLOT(verifyClientResponse(bool)));
    connect(client.data(), SIGNAL(connectionClientInfoPicked()), this, SLOT(onClientInfoPicked()));
}

void NetworkServer::verifyClientResponse(bool isSuccess) {
    NClient client = static_cast<NetworkClient *>(sender());
    disconnect(client.data(), SIGNAL(verified(bool)), this, SLOT(verifyClientResponse(bool)));
    if (isSuccess) {
        emit clientConnected(client);
    } else {
        client->stopClient();
    }
}

void NetworkServer::onClientConnected(NClient client) {
    client->pickInfo();
}

void NetworkServer::onClientInfoPicked() {
    NClient client = static_cast<NetworkClient *>(sender());
    Info(tr("Connected client info: %1 : %2 at %3").arg(client->peerAddress().toString()).arg(client->peerPort()).arg(client->peerName().isEmpty() ? tr ("Unknown host") : client->peerName()));
}
