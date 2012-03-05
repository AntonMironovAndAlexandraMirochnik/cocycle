#include "NetworkController.h"
#include "NetworkConnectionClient.h"
#include "NetworkConnectionServer.h"
#include "Public/NetworkClient.h"
#include "Public/NetworkServer.h"

NetworkController::NetworkController() : QObject(nullptr) {
    qRegisterMetaType<NClient>("NClient");
    qRegisterMetaType<NServer>("NServer");
    qRegisterMetaType<NConnectionClient>("NConnectionClient");
    qRegisterMetaType<NConnectionServer>("NConnectionServer");
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<NetworkConnectionClient::Info>("NetworkConnectionClient::Info");
}

void NetworkController::initClient(NClient client) {
    NConnectionClient connectionClient = NConnectionClient(new NetworkConnectionClient(this));
    QMetaObject::invokeMethod(client, "setConnectionClient", Qt::AutoConnection, Q_ARG(NConnectionClient, connectionClient));
}

void NetworkController::initServer(NServer server) {
    NConnectionServer connectionServer = NConnectionServer(new NetworkConnectionServer(this));
    QMetaObject::invokeMethod(server, "setConnectionServer", Qt::AutoConnection, Q_ARG(NConnectionServer, connectionServer));
}
