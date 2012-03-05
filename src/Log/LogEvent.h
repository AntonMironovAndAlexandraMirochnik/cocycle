#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "LogConstants.h"

class LogEvent : public QEvent {
public:
    LogEvent(QSharedPointer<LogMessage> logMessage);
    QSharedPointer<LogMessage> logMessage() const;

    static const int EventType;

private:
    QSharedPointer<LogMessage> _logMessage;
};

#endif // LOGEVENT_H
