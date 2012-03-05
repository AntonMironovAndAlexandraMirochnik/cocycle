#ifndef LOGCONSTANTS_H
#define LOGCONSTANTS_H

#include <QtCore>

class LogMessage;
class LogEvent;
class LogController;

enum {
    LogInfo = -2,
    LogDebug = -1,
    LogWarning = 0,
    LogCritical = 1,
    LogFatal = 2
};

typedef int LogMessageType;

#endif // LOGCONSTANTS_H
