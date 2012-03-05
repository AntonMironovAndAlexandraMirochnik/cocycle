#include "LoginDialogController.h"
#include "ui_LoginDialogController.h"
#include "Network.h"

LoginDialogController::LoginDialogController(NetworkClient *networkClient, QObject *parent) : QObject(parent) {
    _dialog = new QDialog();
    _ui = new Ui::LoginDialogController();
    ui()->setupUi(dialog());
    connect(ui()->connectButton, SIGNAL(pressed()), this, SLOT(onAccept()));
    connect(dialog(), SIGNAL(rejected()), this, SLOT(onReject()));

    _networkClient = networkClient;
    connect(networkClient, SIGNAL(initialized()), this, SLOT(onClientInitialized()));
    connect(networkClient, SIGNAL(started()), this, SLOT(onClientStarted()));
    connect(networkClient, SIGNAL(stopped()), this, SLOT(onClientStopped()));
    connect(networkClient, SIGNAL(error(int)), this, SLOT(onClientError(int)));

    setStatus("");
}

LoginDialogController::~LoginDialogController() {
    delete ui();
    delete dialog();
}

NetworkClient* LoginDialogController::networkClient() const { return _networkClient; }

QDialog* LoginDialogController::dialog() const { return _dialog; }

Ui::LoginDialogController* LoginDialogController::ui() const { return _ui; }

QString LoginDialogController::status() const { return _status; }

void LoginDialogController::setStatus(const QString &status) {
    _status = status;
    ui()->statusLabel->setText(status);
}

void LoginDialogController::open() {
    dialog()->open();
}

void LoginDialogController::onAccept() {
    startClient();
}

void LoginDialogController::onReject() {
    emit rejected();
}

void LoginDialogController::startClient() {
    QHostAddress host(ui()->addressEdit->text());
    quint16 port = ui()->portEdit->value();
    if (!host.isNull()) {
        setStatus("Connecting...");
        networkClient()->startClient(host, port);
    }
}

void LoginDialogController::onClientInitialized() {
}

void LoginDialogController::onClientStarted() {
    setStatus(QString());
    dialog()->accept();
    emit accepted();
}

void LoginDialogController::onClientStopped() {
}

void LoginDialogController::onClientError(int error) {
    setStatus(tr("Connection error %1").arg(error));
}
