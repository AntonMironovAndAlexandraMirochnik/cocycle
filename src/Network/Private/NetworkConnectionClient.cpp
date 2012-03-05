#include "NetworkConnectionClient.h"

NetworkConnectionClient::NetworkConnectionClient(QObject *parent) : QTcpSocket(parent) {
    connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
}

void NetworkConnectionClient::start(const QHostAddress &address, quint16 port) {
    connectToHost(address, port);
}

void NetworkConnectionClient::stop() {
    disconnectFromHost();
}

void NetworkConnectionClient::write(const QByteArray &data) {
    QTcpSocket::write(data);
}

void NetworkConnectionClient::onConnected() {
    NetworkConnectionClient::Info info;
    info.peerAddress = peerAddress();
    info.peerPort = peerPort();
    info.peerName = peerName();
    emit infoPicked(info);
}
