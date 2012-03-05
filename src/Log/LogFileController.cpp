#include "LogFileController.h"
#include "LogEvent.h"
#include "LogMessage.h"

LogFileController::LogFileController(const QString &fileName) {
    if (!fileName.isEmpty()) {
        setFile(new QFile(fileName));
        file()->open(QFile::Append);
    }
}

LogFileController::~LogFileController() {
    setFile(nullptr);
}

void LogFileController::handleMessage(QSharedPointer<LogMessage> logMessage) {
    if (nullptr == file() || !file()->isWritable()) {
        LogController::handleMessage(logMessage);
    } else {
        file()->write(stringForLogMessage(logMessage).toUtf8());
    }
}

QString LogFileController::stringForLogMessage(QSharedPointer<LogMessage> logMessage) {
    return LogController::stringForLogMessage(logMessage) + "\r\n";
}

QFile* LogFileController::file() const {
    return _file.data();
}

void LogFileController::setFile(QFile* file) {
    if (!_file.isNull()) {
        _file->close();
        _file->deleteLater();
    }
    _file = file;
}
