#include "MainWindowController.h"
#include "ui_MainWindowController.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {
    _window = new QMainWindow();
    _ui = new Ui::MainWindowController();
    ui()->setupUi(window());

    connect(ui()->action_Quit, SIGNAL(triggered()), this, SLOT(onQuit()));
}

MainWindowController::~MainWindowController() {
    delete ui();
    delete window();
}

Ui::MainWindowController* MainWindowController::ui() const { return _ui; }
QMainWindow* MainWindowController::window() const { return _window; }

void MainWindowController::onQuit() {
    window()->close();
    emit shouldQuit();
}
