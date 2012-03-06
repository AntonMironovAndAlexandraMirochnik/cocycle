#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QtCore>

class MainWindow;

class MainWindowController : public QObject {
    Q_OBJECT
    
public:
    explicit MainWindowController(QObject *parent = 0);
    ~MainWindowController();

    MainWindow* window() const;

public slots:
    void showWindow();

protected slots:
    void onWindowShouldQuit();
    void onWindowClosed();

    void quit();
    
private:
    QPointer<MainWindow> _window;

signals:
    void shouldQuit();
};

#endif // MAINWINDOWCONTROLLER_H
