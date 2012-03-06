#include "MainWindowController.h"
#include "MainWindow.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {
    _window = new MainWindow();
    connect(window(), SIGNAL(shouldQuit()), this, SLOT(onWindowShouldQuit()));
    connect(window(), SIGNAL(closed()), this, SLOT(onWindowClosed()));
}

MainWindowController::~MainWindowController() {
    delete window();
}

MainWindow *MainWindowController::window() const { return _window; }

void MainWindowController::onWindowClosed() {
    quit();
}

void MainWindowController::onWindowShouldQuit() {
    window()->close();
}

void MainWindowController::showWindow() {
    window()->show();
}

void MainWindowController::quit() {
    emit shouldQuit();
}
