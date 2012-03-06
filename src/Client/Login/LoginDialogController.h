#ifndef LOGINDIALOGCONTROLLER_H
#define LOGINDIALOGCONTROLLER_H

#include <QtCore>

class LoginWidget;
class NetworkClient;

class LoginDialogController : public QObject {
    Q_OBJECT
    
public:
    explicit LoginDialogController(QObject *parent = 0);
    ~LoginDialogController();

    void setNetworkClient(NetworkClient* networkClient_);
    bool isInProgress();
    void launchDialog();

public slots:
    void accept();
    void reject();

signals:
    void accepted();
    void rejected();

protected:
    NetworkClient* networkClient() const;
    LoginWidget* loginWidget() const;

protected slots:
    void onClientStarted();
    void onClientStopped();
    void onClientError(int errorNo);

    void onAcceptAttempt();
    void onRejectAttempt();

    void onWindowClosed();

    void startClient();
private:
    QPointer<NetworkClient> _networkClient;
    QPointer<LoginWidget> _loginWidget;
    bool _isInProgress;


};

#endif // LOGINDIALOGCONTROLLER_H
