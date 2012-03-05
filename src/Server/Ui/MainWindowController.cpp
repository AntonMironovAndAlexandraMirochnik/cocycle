#include "MainWindowController.h"
#include "ui_MainWindow.h"
#include <QHostAddress>
#include <QNetworkInterface>

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {
    _window = new QMainWindow();
    _ui = new Ui::MainWindow();
    ui()->setupUi(window());

    connect(ui()->startServerButton, SIGNAL(pressed()), this, SLOT(onStartServerButton()));
    connect(ui()->stopServerButton, SIGNAL(pressed()), this, SLOT(onStopServerButton()));
    connect(ui()->quitButton, SIGNAL(pressed()), this, SLOT(onQuit()));
    connect(ui()->hostListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(onHostListSelectionChanged()));

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (QList<QHostAddress>::const_iterator index = ipAddressesList.constBegin(); ipAddressesList.constEnd() != index; ++index) {
        ui()->hostListWidget->addItem((*index).toString());
    }
}

MainWindowController::~MainWindowController() {
    window()->deleteLater();
    delete ui();
}

Ui::MainWindow* MainWindowController::ui() const {
    return _ui;
}

QMainWindow* MainWindowController::window() const {
    return _window;
}

void MainWindowController::onStartServerButton() {
    QString address = ui()->addressEdit->text();
    quint16 port = ui()->portEdit->value();
    emit shouldStartServer(address, port);
}

void MainWindowController::onStopServerButton() {
    emit shouldStopServer();
}

void MainWindowController::onQuit() {
    window()->close();
    emit shouldQuit();
}

void MainWindowController::onHostListSelectionChanged() {
    ui()->addressEdit->setText(ui()->hostListWidget->selectedItems().first()->text());
}

void MainWindowController::showWindow() {
    window()->show();
}

