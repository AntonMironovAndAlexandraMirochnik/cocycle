#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QtGui>

namespace Ui {
class MainWindowController;
}

class MainWindowController : public QObject
{
    Q_OBJECT
    
public:
    explicit MainWindowController(QObject *parent = 0);
    ~MainWindowController();

    QMainWindow* window() const;

protected:
    Ui::MainWindowController* ui() const;

protected slots:
    void onQuit();
    
private:
    Ui::MainWindowController *_ui;
    QPointer<QMainWindow> _window;

signals:
    void shouldQuit();
};

#endif // MAINWINDOWCONTROLLER_H
