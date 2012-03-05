#include "NetworkThread.h"
#include "NetworkServer.h"
#include "NetworkClient.h"
#include "Private/NetworkController.h"

HostAddress::HostAddress() {
    isValid = true;
}

HostAddress::HostAddress(const QString &hostString) {
    QStringList chunks = hostString.split(":");
    QString hostAddressString;
    QString portString = "0";
    switch (chunks.count()) {
    case 1:
        hostAddressString = chunks.at(0).trimmed();
        break;
    case 2:
        hostAddressString = chunks.at(0).trimmed();
        portString = chunks.at(1).trimmed();
        break;
    }

    hostAddress = QHostAddress(hostAddressString);
    isValid = true;
    if (!portString.isEmpty()) {
        port = portString.toInt(&isValid);
    }
    isValid = isValid && !hostAddress.isNull();
}

NetworkThread::NetworkThread(QObject *parent) : QThread(parent) {
    Info(tr("Network thread created."));
}

NetworkThread::~NetworkThread() {
    Info(tr("Network thread destroyed."));
}

void NetworkThread::run() {
    NetworkController controller;
    _controller = &controller;
    connect(this, SIGNAL(clientCreated(NClient)), &controller, SLOT(initClient(NClient)));
    connect(this, SIGNAL(serverCreated(NServer)), &controller, SLOT(initServer(NServer)));
    emit initialized();
    exec();
}

NClient NetworkThread::createClient(QObject *parent) {
    NClient client = NClient(new NetworkClient(parent));
    connect(this, SIGNAL(finished()), client.data(), SLOT(deleteLater()));
    emit clientCreated(client);
    return client;
}

NServer NetworkThread::createServer(QObject *parent) {
    NServer server = NServer(new NetworkServer(parent));
    connect(this, SIGNAL(finished()), server.data(), SLOT(deleteLater()));
    emit serverCreated(server);
    return server;
}
