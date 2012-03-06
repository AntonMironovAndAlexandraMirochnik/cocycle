#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    
signals:
    void shouldQuit();
    void closed();
    
public slots:

protected:
    Ui::MainWindow* ui() const;
    void closeEvent(QCloseEvent *event);

protected slots:
    void onQuitAction();

private:
    Ui::MainWindow* _ui;
};

#endif // MAINWINDOW_H
