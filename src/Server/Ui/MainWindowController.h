#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

namespace Ui {
class MainWindow;
}

class UiServerDelegate;

class MainWindowController : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowController(QObject *parent = 0);
    virtual ~MainWindowController();

public slots:
    void showWindow();

protected:
    Ui::MainWindow* ui() const;
    QMainWindow* window() const;

protected slots:
    void onStartServerButton();
    void onStopServerButton();
    void onQuit();
    void onHostListSelectionChanged();

private:
    Ui::MainWindow* _ui;
    QMainWindow* _window;

signals:
    void shouldStartServer(const QString &address, quint16 port);
    void shouldStopServer();
    void shouldQuit();
};

#endif // MAINWINDOW_H
