#include "NetworkClient.h"
#include "NetworkServer.h"

const QString NetworkClient::VerificationString("I am the hair.");

NetworkClient::NetworkClient(QObject* parent, int id_) :  QObject(parent), id(id_) {
    _isVerified = false;
    _peerPort = 0;
}

void NetworkClient::setConnectionClient(NConnectionClient connectionClient) {
    _connectionClient = connectionClient;
    connect(connectionClient.data(), SIGNAL(connected()), this, SLOT(onConnectionClientConnected()));
    connect(connectionClient.data(), SIGNAL(disconnected()), this, SLOT(onConnectionClientDisconnected()));
    connect(connectionClient.data(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(connectionClient.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(connectionClient.data(), SIGNAL(infoPicked(NetworkConnectionClient::Info)), this, SLOT(onConnectionClientInfoPicked(NetworkConnectionClient::Info)));
    emit initialized();
    if (isOnServerSide()) {
        onConnectionClientConnected();
    }
}

NConnectionClient NetworkClient::connectionClient() const { return _connectionClient; }

bool NetworkClient::isVerified() const { return _isVerified; }
bool NetworkClient::isOnServerSide() const { return 0 != id; }

QHostAddress NetworkClient::peerAddress() const { return _peerAddress; }
quint16 NetworkClient::peerPort() const { return _peerPort; }
QString NetworkClient::peerName() const { return _peerName; }

void NetworkClient::startClient(const QHostAddress &address, quint16 port) {
    QMetaObject::invokeMethod(connectionClient(), "start", Q_ARG(QHostAddress, address), Q_ARG(quint16, port));
}

void NetworkClient::stopClient() {
    QMetaObject::invokeMethod(connectionClient(), "stop");
}

void NetworkClient::onConnectionClientConnected() {
    QString string = isOnServerSide() ? NetworkServer::VerificationString : NetworkClient::VerificationString;
    sendData(string.toUtf8());
}

void NetworkClient::onConnectionClientDisconnected() {
    emit stopped();
}

void NetworkClient::onError(QAbstractSocket::SocketError socketError) {
    emit error(static_cast<int>(socketError));
}

void NetworkClient::onReadyRead() {
    QByteArray data = connectionClient()->readAll();
    if (isVerified()) {
        emit incomingData(data);
    } else {
        _isVerified  = isOnServerSide() ? (NetworkClient::VerificationString == data) : (NetworkServer::VerificationString == data);
        if (isVerified()) {
            emit started();
            Info(tr("Client connected."));
        } else {
            stopClient();
            Warning(tr("Client verification failed."));
        }
    }
}

void NetworkClient::onConnectionClientInfoPicked(const NetworkConnectionClient::Info &info) {
    _peerAddress = info.peerAddress;
    _peerPort = info.peerPort;
    _peerName = info.peerName;
}

void NetworkClient::sendData(const QByteArray &data) {
    QMetaObject::invokeMethod(connectionClient(), "write", Q_ARG(QByteArray, data));
}
