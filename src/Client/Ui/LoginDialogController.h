#ifndef LOGINDIALOGCONTROLLER_H
#define LOGINDIALOGCONTROLLER_H

#include <QtGui>
#include "Network.h"

namespace Ui {
class LoginDialogController;
}

class LoginDialogController : public QObject {
    Q_OBJECT
    
public:
    explicit LoginDialogController(NetworkClient *networkClient, QObject *parent = 0);
    ~LoginDialogController();
    
public slots:
    void open();

protected:
    NetworkClient* networkClient() const;
    QDialog* dialog() const;
    Ui::LoginDialogController* ui() const;

    QString status() const;
    void setStatus(const QString &status);

    void startClient();

protected slots:
    void onAccept();
    void onReject();
    void onClientInitialized();
    void onClientStarted();
    void onClientStopped();
    void onClientError(int error);

private:
    Ui::LoginDialogController *_ui;
    QPointer<NetworkClient> _networkClient;
    QPointer<QDialog> _dialog;
    QString _status;

signals:
    void accepted();
    void rejected();
};

#endif // LOGINDIALOGCONTROLLER_H
