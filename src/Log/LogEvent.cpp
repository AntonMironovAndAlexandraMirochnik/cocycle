#include "LogEvent.h"
#include "LogMessage.h"

const int LogEvent::EventType = QEvent::registerEventType();

LogEvent::LogEvent(QSharedPointer<LogMessage> logMessage) : QEvent(static_cast<QEvent::Type>(LogEvent::EventType)), _logMessage(logMessage) {
}

QSharedPointer<LogMessage> LogEvent::logMessage() const {
    return _logMessage;
}
