#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include "Private/NetworkConstants.h"

class NetworkServer : public QObject {
    Q_OBJECT

public:
    static const QString VerificationString;
    explicit NetworkServer(QObject* parent = 0);

public slots:
    void setConnectionServer(NConnectionServer connectionServer);
    void startServer(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    void stopServer();

protected:
    NConnectionServer connectionServer() const;

protected slots:
    virtual void onConnectionClientConnected(NConnectionClient connectionClient);
    virtual void onClientConnected(NClient client);
    virtual void onClientInfoPicked();

private:
    NConnectionServer _connectionServer;
    QMap<int, NClient> _clients;
    int _lastClientId;

private slots:
    void verifyClientResponse(bool isSuccess);

signals:
    void initialized();
    void clientConnected(NClient client);
};

#endif // NETWORKSERVER_H
