#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include "LogConstants.h"

class LogMessage
{
public:
    LogMessage(const QString &text, LogMessageType type, const QDateTime &dateTime, unsigned int indent);
    virtual ~LogMessage();
    virtual QString toString() const;
    QString operator()() const;

    virtual QString text() const;
    virtual LogMessageType type() const;
    virtual QDateTime dateTime() const;
    virtual unsigned int indent() const;
protected:

    virtual QString textString() const;
    virtual QString typeString() const;
    virtual QString dateTimeString() const;
    virtual QString indentString() const;

private:
    const QString _text;
    const LogMessageType _type;
    const QDateTime _dateTime;
    const unsigned int _indent;
};

#endif // LOGMESSAGE_H
