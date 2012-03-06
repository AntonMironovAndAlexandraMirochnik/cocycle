#include "LoginDialogController.h"
#include "Network.h"
#include "LoginWidget.h"

LoginDialogController::LoginDialogController(QObject *parent) : QObject(parent) {
    _isInProgress = false;
    _loginWidget = new LoginWidget();
    connect(loginWidget(), SIGNAL(acceptAttempt()), this, SLOT(onAcceptAttempt()));
    connect(loginWidget(), SIGNAL(rejectAttempt()), this, SLOT(onRejectAttempt()));
}

LoginDialogController::~LoginDialogController() {
    delete _loginWidget;
}

NetworkClient* LoginDialogController::networkClient() const { return _networkClient; }

LoginWidget* LoginDialogController::loginWidget() const { return _loginWidget; }

void LoginDialogController::setNetworkClient(NetworkClient* networkClient_) {
    if (nullptr != networkClient()) {
        disconnect(networkClient(), SIGNAL(started()), this, SLOT(onClientStarted()));
        disconnect(networkClient(), SIGNAL(stopped()), this, SLOT(onClientStopped()));
        disconnect(networkClient(), SIGNAL(error(int)), this, SLOT(onClientError(int)));
    }
    _networkClient = networkClient_;

    if (nullptr != networkClient()) {
        connect(networkClient(), SIGNAL(started()), this, SLOT(onClientStarted()));
        connect(networkClient(), SIGNAL(stopped()), this, SLOT(onClientStopped()));
        connect(networkClient(), SIGNAL(error(int)), this, SLOT(onClientError(int)));

        if (networkClient()->isNotConnected()) {
            launchDialog();
        }
    }
}

void LoginDialogController::startClient() {
    QHostAddress host(loginWidget()->address());
    quint16 port = loginWidget()->port();
    if (host.isNull() && loginWidget()->isAttempingToAccept()) {
        loginWidget()->responseToAcceptAttempt(tr("Entered address is invalid."));
    } else {
        networkClient()->startClient(host, port);
    }
}

void LoginDialogController::onClientStarted() {
    if (loginWidget()->isAttempingToAccept())
    {
        loginWidget()->responseToAcceptAttempt();
    }
}

void LoginDialogController::onClientStopped() {
    launchDialog();
}

void LoginDialogController::onClientError(int error) {
    QString errorString = tr("Connectio error %1").arg(error);
    if (loginWidget()->isAttempingToAccept())
    {
        loginWidget()->responseToAcceptAttempt(errorString);
    } else if (loginWidget()->isAttempingToReject()) {
        loginWidget()->responseToRejectAttempt(errorString);
    } else {
        //ToDo
    }
}

void LoginDialogController::onAcceptAttempt() {
    if (networkClient()->isAlive()) {
        loginWidget()->responseToAcceptAttempt();
    } else if (networkClient()->isConnecting()) {
        Warning(tr("Login controller: trying to connect while already connecting"));
    } else {
        startClient();
    }
}

void LoginDialogController::onRejectAttempt() {
    loginWidget()->responseToRejectAttempt();
}

void LoginDialogController::launchDialog() {
    loginWidget()->setWindowModality(Qt::ApplicationModal);
    loginWidget()->show();
}
