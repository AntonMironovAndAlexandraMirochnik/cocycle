#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QtCore>

class NetworkThread;
class NetworkServer;
class NetworkClient;
class MainWindowController;

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);
    virtual ~MainController();
    
signals:

public slots:
    void start();
    void stop();

protected:
    NetworkThread* networkThread() const;
    NetworkServer* networkServer() const;
    MainWindowController* mainWindowController() const;

protected slots:
    void networkThreadInitialized();
    void onShouldStartServer(const QString &addressString, quint16 port = 0);
    void onClientConnected(NetworkClient* client);

private:
    QPointer<NetworkThread> _networkThread;
    QPointer<NetworkServer> _networkServer;
    QPointer<MainWindowController> _mainWindowController;

};

#endif // MAINCONTROLLER_H
