#ifndef LOGCSTYLE_H
#define LOGCSTYLE_H

#include "LogConstants.h"

//C-style functions
void Info(const QString& msg);
void Warning(const QString& msg);
void Debug(const QString& msg);
void Critical(const QString& msg);
void Fatal(const QString& msg);
void LogStartSection();
void LogFinishSection();

#endif // LOGCSTYLE_H
