#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QtGui>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget {
    Q_OBJECT
    
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    bool isAttempingToAccept() const;
    bool isAttempingToReject() const;
    QString address() const;
    quint16 port() const;
    QString login() const;
    QByteArray password() const;

public slots:
    void attemptToAccept();
    void attemptToReject();
    void responseToAcceptAttempt(const QString &errorString = QString());
    void responseToRejectAttempt(const QString &errorString = QString());
    void validateControls();

signals:
    void acceptAttempt();
    void rejectAttempt();
    void closed();
    
protected:
    virtual void closeEvent(QCloseEvent *event);
    bool canClose() const;
    QString status() const;
    bool isEnteredDataValid() const;

    void setStatus(const QString &status);

private:
    Ui::LoginWidget *ui;
    bool _isAttempingToAccept;
    bool _isAttempingToReject;
    QString _status;
};

#endif // LOGINWIDGET_H
