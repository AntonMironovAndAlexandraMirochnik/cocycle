#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include "Private/NetworkConstants.h"

struct HostAddress {
    QHostAddress hostAddress;
    quint16 port;
    bool isValid;
    HostAddress();
    HostAddress(const QString &hostString);
};

class NetworkThread : public QThread {
    Q_OBJECT
public:
    explicit NetworkThread(QObject *parent = 0);
    virtual ~NetworkThread();

public:
    NClient createClient(QObject *parent = 0);
    NServer createServer(QObject *parent = 0);

signals:
    void initialized();
    void clientCreated(NClient);
    void serverCreated(NServer);

protected:
    virtual void run();
    NetworkController* controller() const;

protected slots:

private:
    QPointer<NetworkController> _controller;

};

#endif // NETWORKTHREAD_H
