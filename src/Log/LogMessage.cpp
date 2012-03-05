#include "LogMessage.h"

LogMessage::LogMessage(const QString &text, LogMessageType type, const QDateTime &dateTime, unsigned int indent) :
    _text(text), _type(type), _dateTime(dateTime), _indent(indent) {
}

LogMessage::~LogMessage() {
}

QString LogMessage::text() const {
    return _text;
}

LogMessageType LogMessage::type() const {
    return _type;
}

QDateTime LogMessage::dateTime() const {
    return _dateTime;
}

unsigned int LogMessage::indent() const {
    return _indent;
}

QString LogMessage::textString() const {
    return text();
}

QString LogMessage::typeString() const {
    QString result = 0;
    switch (type()) {
    case LogInfo: result = "<info>";
        break;
    case LogDebug: result = "<debug>";
        break;
    case LogWarning: result = "<warn>";
        break;
    case LogCritical: result = "<crit>";
        break;
    case LogFatal: result = "<fatal>";
        break;
    }
    return result;
}

QString LogMessage::dateTimeString() const {
    return dateTime().toString("[yyyy-MM-dd hh:mm:ss]");
}

QString LogMessage::indentString() const {
    QByteArray data(indent(), '\t');
    return QString(data);
}

QString LogMessage::toString() const {
    return QString("%1%2%3\t: %4").arg(indentString(), dateTimeString(), typeString(), textString());
}

QString LogMessage::operator()() const {
    return toString();
}
