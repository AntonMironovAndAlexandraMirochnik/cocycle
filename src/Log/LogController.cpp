#include "LogController.h"
#include "LogEvent.h"
#include "LogMessage.h"

QPointer<LogController> LogController::_instance = nullptr;

LogController* LogController::instance() {
    if (_instance.isNull()) {
        _instance = new LogController();
    }
    return _instance.data();
}

LogController::LogController() {
    _indent = 0;
}

LogController::~LogController() {
}

void LogController::info(const QString &msg_) {
    log(msg_, LogInfo);
}

void LogController::warning(const QString &msg_) {
    log(msg_, LogWarning);
}

void LogController::debug(const QString &msg_) {
    log(msg_, LogDebug);
}

void LogController::critical(const QString &msg_) {
    log(msg_, LogCritical);
}

void LogController::fatal(const QString &msg_) {
    log(msg_, LogFatal);
}

void LogController::log(const QString &msg_, LogMessageType msgType_) {
    LogMessage* message = logMessage(msg_, msgType_);
    if (QThread::currentThread() == QCoreApplication::instance()->thread())
    {
        _handleMessage(QSharedPointer<LogMessage>(message));
    }
    else
    {
        LogEvent* event = new LogEvent(QSharedPointer<LogMessage>(message));
        QCoreApplication::instance()->postEvent(this, event);
    }
}

void LogController::startSection() {
    ++_indent;
}

void LogController::finishSection() {
    Q_ASSERT(_indent > 0);
    --_indent;
}

unsigned int LogController::indent() const {
    return _indent;
}

QIODevice* LogController::device() const {
    return _device;
}

void LogController::setDevice(QIODevice *device) {
    _device = device;
}

LogMessage* LogController::logMessage(const QString &msg, LogMessageType msgType) {
    LogMessage *result = new LogMessage(msg, msgType, QDateTime::currentDateTime(), indent());
    return result;
}

QString LogController::stringForLogMessage(QSharedPointer<LogMessage> logMessage) {
    return logMessage->toString();
}

void LogController::_handleMessage(QSharedPointer<LogMessage> logMessage) {
    emit logMessageAppeared(logMessage);
    handleMessage(logMessage);
}

void LogController::handleMessage(QSharedPointer<LogMessage> logMessage) {
    qDebug() << stringForLogMessage(logMessage);

    if (LogFatal == logMessage->type()) {
        QCoreApplication::instance()->quit();
    }
}

void LogController::customEvent(QEvent *event) {
    if (event->type() == LogEvent::EventType) {
        LogEvent* logEvent = static_cast<LogEvent *>(event);
        _handleMessage(logEvent->logMessage());
    } else {
        QObject::customEvent(event);
    }
}
