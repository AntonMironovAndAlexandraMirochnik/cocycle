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
    bool isAlive() const;
    bool isNotConnected() const;
    bool isConnecting() const;
    bool isDisconnecting() const;
    QHostAddress peerAddress() const;
    quint16 peerPort() const;
    QString peerName() const;


public slots:
    void setConnectionClient(NConnectionClient connectionClient);
    void startClient(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    void stopClient();
    void sendVariantObject(const QVariant &variant);
    void pickInfo();

protected:
    NConnectionClient connectionClient() const;

protected slots:
    void sendData(const QByteArray &data);

    void onReadyRead();
    void onConnectionClientConnected();
    void onConnectionClientDisconnected();
    void onIncomingDataProcessingFinished();
    void onOutcomingDataProcessingFinished();
    void onError(QAbstractSocket::SocketError socketError);
    void onConnectionClientInfoPicked(const NetworkConnectionClient::Info &info);
    void onIncomingData(const QByteArray &data);

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
    void incomingVariantObject(const QVariant &variant);
    void verified(bool isSuccess);
    void connectionClientInfoPicked();

    friend class NetworkServer;
};

#endif // NETWORKCLIENT_H
