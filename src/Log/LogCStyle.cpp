#include "LogCStyle.h"
#include "LogController.h"

void Info(const QString& msg) {
    LogController::instance()->info(msg);
}
void Warning(const QString& msg) {
    LogController::instance()->warning(msg);
}
void Debug(const QString& msg) {
    LogController::instance()->debug(msg);
}
void Critical(const QString& msg) {
    LogController::instance()->critical(msg);
}
void Fatal(const QString& msg) {
    LogController::instance()->fatal(msg);
}
void LogStartSection() {
    LogController::instance()->startSection();
}
void LogFinishSection() {
    LogController::instance()->finishSection();
}
