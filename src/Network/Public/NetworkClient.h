#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "Private/NetworkConstants.h"
#include "Private/NetworkConnectionClient.h"

class NetworkClient : public QObject {
    Q_OBJECT

public:
    static const QString VerificationString;
    const int id;

    explicit NetworkClient(QObject* parent = 0, int id_ = 0);
    bool isVerified() const;
    bool isOnServerSide() const;
    QHostAddress peerAddress() const;
    quint16 peerPort() const;
    QString peerName() const;


public slots:
    void setConnectionClient(NConnectionClient connectionClient);
    void startClient(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    void stopClient();
    void sendData(const QByteArray &data);

    void onConnectionClientConnected();
    void onConnectionClientDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
    void onReadyRead();
    void onConnectionClientInfoPicked(const NetworkConnectionClient::Info &info);

protected:
    NConnectionClient connectionClient() const;

private:
    NConnectionClient _connectionClient;
    bool _isVerified;
    QHostAddress _peerAddress;
    quint16 _peerPort;
    QString _peerName;

signals:
    void initialized();
    void started();
    void stopped();
    void error(int error);
    void incomingData(const QByteArray &data);
    void verified(bool isSuccess);

    friend class NetworkServer;
};

#endif // NETWORKCLIENT_H
