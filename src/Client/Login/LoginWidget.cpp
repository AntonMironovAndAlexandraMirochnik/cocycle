#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include "Log.h"

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LoginWidget) {
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    connect(ui->connectButton, SIGNAL(pressed()), this, SLOT(attemptToAccept()));
    connect(ui->addressEdit, SIGNAL(textChanged(QString)), this, SLOT(validateControls()));
    connect(ui->loginEdit, SIGNAL(textChanged(QString)), this, SLOT(validateControls()));
    connect(ui->passwordEdit, SIGNAL(textChanged(QString)), this, SLOT(validateControls()));
    connect(this, SIGNAL(acceptAttempt()), this, SLOT(validateControls()));
    connect(this, SIGNAL(rejectAttempt()), this, SLOT(validateControls()));
    setStatus("");
    _isAttempingToAccept = false;
    _isAttempingToReject = false;
    validateControls();
}

LoginWidget::~LoginWidget() {
    delete ui;
}

bool LoginWidget::canClose() const { return !isAttempingToAccept() && !isAttempingToReject(); }
bool LoginWidget::isAttempingToAccept() const { return _isAttempingToAccept; }
bool LoginWidget::isAttempingToReject() const { return _isAttempingToReject; }
QString LoginWidget::status() const { return _status; }
QString LoginWidget::address() const {
    return ui->addressEdit->text();
}
quint16 LoginWidget::port() const {
    return ui->portEdit->value();
}
QString LoginWidget::login() const {
    return ui->loginEdit->text();
}
QByteArray LoginWidget::password() const {
    QString password = ui->passwordEdit->text();
    return (password.isEmpty()) ? password.toUtf8() : QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1);
}

bool LoginWidget::isEnteredDataValid() const {
    return !(address().isEmpty() || login().isEmpty() || password().isEmpty());
}

void LoginWidget::setStatus(const QString &status) {
    _status = status;
    ui->statusLabel->setText(status);
}

void LoginWidget::closeEvent(QCloseEvent *event) {
    if (isVisible())
    {
        if (canClose()) {
            event->accept();
            emit closed();
        } else {
            event->ignore();
            QMetaObject::invokeMethod(this, "attemptToReject", Qt::QueuedConnection);
        }
    }
}

void LoginWidget::validateControls() {
    ui->connectButton->setEnabled(isEnteredDataValid());
    setEnabled(!isAttempingToAccept() && !isAttempingToReject());
}

void LoginWidget::attemptToAccept() {
    if (isAttempingToAccept()) {
        Warning(tr("Attempting to log in when one attempt is already on."));
    } else {
        setStatus(tr("Attempting to log in..."));
        _isAttempingToAccept = true;
        emit acceptAttempt();
    }
}

void LoginWidget::attemptToReject() {
    if (isAttempingToReject()) {
        Warning(tr("Attempting to reject when one attempt is already on."));
    } else {
        setStatus(tr("Attempting to reject..."));
        emit rejectAttempt();
    }
}

void LoginWidget::responseToAcceptAttempt(const QString &errorString) {
    _isAttempingToAccept = false;
    if (errorString.isEmpty()) {
        close();
    } else {
        validateControls();
        setStatus(errorString);
    }
}

void LoginWidget::responseToRejectAttempt(const QString &errorString) {
    _isAttempingToReject = false;
    if (errorString.isEmpty()) {
        close();
    } else {
        validateControls();
        setStatus(errorString);
    }
}
