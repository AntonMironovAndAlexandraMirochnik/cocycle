#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QtCore>

class NetworkThread;
class NetworkClient;
class MainWindowController;
class LoginDialogController;

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
    //init components
    NetworkClient* networkClient() const;
    void initNetworkClient();

    NetworkThread* networkThread() const;
    void initNetworkThread();

    MainWindowController* mainWindowController() const;
    void initMainWindowController();

    LoginDialogController* loginDialogController() const;
    void initLoginDialogController();

protected slots:
    void onNetworkThreadInitialized();
    void onNetworkClientStarted();

private:
    QPointer<NetworkThread> _networkThread;
    QPointer<NetworkClient> _networkClient;
    QPointer<MainWindowController> _mainWindowController;
    QPointer<LoginDialogController> _loginDialogController;

};

#endif // MAINCONTROLLER_H
