#ifndef LOGFILECONTROLLER_H
#define LOGFILECONTROLLER_H

#include "LogController.h"

class LogFileController : public LogController
{
    Q_OBJECT
    Q_PROPERTY (QFile* file READ file WRITE setFile)

public:
    LogFileController(const QString &fileName = QString());
    virtual ~LogFileController();

    virtual void handleMessage(QSharedPointer<LogMessage> logMessage);
    virtual QString stringForLogMessage(QSharedPointer<LogMessage> logMessage);

    QFile* file() const;

protected:
    void setFile(QFile* file);

private:
    QPointer<QFile> _file;
};

#endif // LOGFILECONTROLLER_H
