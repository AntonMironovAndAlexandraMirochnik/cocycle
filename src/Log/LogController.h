#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include "LogConstants.h"
#include "LogMessage.h"

class LogController : public QObject {
    Q_OBJECT
public:
    static LogController* instance();

    virtual ~LogController();

    void info(const QString &msg_);
    void warning(const QString &msg_);
    void debug(const QString &msg_);
    void critical(const QString &msg_);
    void fatal(const QString &msg_);
    void log(const QString &msg_, LogMessageType msgType_ = LogWarning);
    void startSection();
    void finishSection();
    unsigned int indent() const;

    QIODevice* device() const;
    void setDevice(QIODevice *device);

protected:
    LogController();

    virtual LogMessage* logMessage(const QString &msg, LogMessageType msgType);
    virtual QString stringForLogMessage(QSharedPointer<LogMessage> logMessage);
    virtual void handleMessage(QSharedPointer<LogMessage> logMessage);

    void customEvent(QEvent *event);

private:
    static QPointer<LogController> _instance;
    unsigned int _indent;
    QPointer<QIODevice> _device;
    void _handleMessage(QSharedPointer<LogMessage> logMessage);

signals:
    void logMessageAppeared(QSharedPointer<LogMessage> logMessage);
};

#endif // LOGCONTROLLER_H
