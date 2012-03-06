#ifndef NETWORKCONNECTIONCLIENT_H
#define NETWORKCONNECTIONCLIENT_H

#include "NetworkConstants.h"

class NetworkConnectionClient : public QTcpSocket {
    Q_OBJECT
public:
    struct Info {
        QHostAddress peerAddress;
        quint16 peerPort;
        QString peerName;
    };

    explicit NetworkConnectionClient(QObject *parent = 0);

public slots:
    virtual void start(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    virtual void stop();
    virtual void write(const QByteArray &data);
    virtual void pickInfo();

signals:
    void infoPicked(const NetworkConnectionClient::Info &info);

protected:

protected slots:
    void onConnected();

};

Q_DECLARE_METATYPE(NetworkConnectionClient::Info)

#endif // NETWORKCONNECTIONCLIENT_H
