#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtCore>
#include <QApplication>

class MainController;

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char** argv);
    
signals:
    
public slots:
    int exec();

protected:
    MainController* mainController() const;

private:
    QPointer<MainController> _mainController;
};

#endif // APPLICATION_H
