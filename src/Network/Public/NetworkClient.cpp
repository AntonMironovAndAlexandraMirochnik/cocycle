#include "NetworkClient.h"
#include "NetworkServer.h"
#include "Serializers.h"

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
bool NetworkClient::isAlive() const {
    return (nullptr != connectionClient() && connectionClient()->state() == QAbstractSocket::ConnectedState);
}
bool NetworkClient::isNotConnected() const {
    return (nullptr == connectionClient() || connectionClient()->state() == QAbstractSocket::UnconnectedState);
}
bool NetworkClient::isConnecting() const {
    return (nullptr != connectionClient() && (connectionClient()->state() == QAbstractSocket::ConnectingState || connectionClient()->state() == QAbstractSocket::HostLookupState));
}
bool NetworkClient::isDisconnecting() const {
    return (nullptr != connectionClient() && connectionClient()->state() == QAbstractSocket::ClosingState);
}

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
        emit verified(isVerified());
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
    emit connectionClientInfoPicked();
}

void NetworkClient::onIncomingData(const QByteArray &data) {
    if (data.size() <= MaxUnthreadedProcessingDataSize) {
        VBackwardSerializer deserializer = VariantBackwardSerializer::Deserialize(data);
        QVariant variantObject = deserializer->variant();
        if (deserializer->isValid()) {
            emit incomingVariantObject(variantObject);
        } else {
            Warning("Incoming data procession error.");
        }
        delete deserializer;
    } else {
        QFutureWatcher<VBackwardSerializer>* futureWatcher = new QFutureWatcher<VBackwardSerializer>();
        connect(futureWatcher, SIGNAL(finished()), this, SLOT(onIncomingDataProcessingFinished()));
        QFuture<VBackwardSerializer> future = QtConcurrent::run(VariantBackwardSerializer::Deserialize, data);
        futureWatcher->setFuture(future);
    }
}

void NetworkClient::onIncomingDataProcessingFinished() {
    QFutureWatcher<VBackwardSerializer>* futureWatcher = static_cast<QFutureWatcher<VBackwardSerializer> *>(sender());
    VBackwardSerializer deserializer = futureWatcher->result();
    QVariant variantObject = deserializer->variant();
    if (deserializer->isValid()) {
        emit incomingVariantObject(variantObject);
    } else {
        Warning("Incoming data procession error.");
    }
    delete deserializer;
}

void NetworkClient::onOutcomingDataProcessingFinished() {
    QFutureWatcher<VSerializer>* futureWatcher = static_cast<QFutureWatcher<VSerializer> *>(sender());
    VSerializer serializer = futureWatcher->result();
    QByteArray data = serializer->data();
    if (serializer->isValid()) {
        sendData(data);
    } else {
        Warning("Incoming data procession error.");
    }
    delete serializer;
}

void NetworkClient::sendData(const QByteArray &data) {
    QMetaObject::invokeMethod(connectionClient(), "write", Q_ARG(QByteArray, data));
}

void NetworkClient::sendVariantObject(const QVariant &variant) {
    QFutureWatcher<VSerializer>* futureWatcher = new QFutureWatcher<VSerializer>();
    connect(futureWatcher, SIGNAL(finished()), this, SLOT(onOutcomingDataProcessingFinished()));
    QFuture<VSerializer> future = QtConcurrent::run(VariantSerializer::Serialize, variant);
    futureWatcher->setFuture(future);
}

void NetworkClient::pickInfo() {
    QMetaObject::invokeMethod(connectionClient().data(), "pickInfo");
}
