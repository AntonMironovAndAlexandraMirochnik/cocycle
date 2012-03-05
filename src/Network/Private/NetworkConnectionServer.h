#ifndef NETWORKCONNECTIONSERVER_H
#define NETWORKCONNECTIONSERVER_H

#include "NetworkConstants.h"

class NetworkConnectionServer : public QTcpServer {
    Q_OBJECT
public:
    explicit NetworkConnectionServer(QObject *parent = 0);

public slots:
    virtual void start(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    virtual void stop();

protected:
    void timerEvent(QTimerEvent *timerEvent);
    virtual void incomingConnection(int handle);

private:
    int networkStatusTimer;
    void checkStatus();

signals:
    void errorAppeared(const QString &error);
    void newConnectionClient(NConnectionClient connectionClient);
};

#endif // NETWORKCONNECTIONSERVER_H
