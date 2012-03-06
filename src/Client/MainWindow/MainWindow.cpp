#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    _ui = new Ui::MainWindow();
    ui()->setupUi(this);

    connect(ui()->action_Quit, SIGNAL(triggered()), this, SLOT(onQuitAction()));
}

MainWindow::~MainWindow() {
    delete _ui;
}

Ui::MainWindow* MainWindow::ui() const { return _ui; }

void MainWindow::onQuitAction() {
    emit shouldQuit();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (isVisible()) {
        event->accept();
        emit closed();
    }
}
