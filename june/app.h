#ifndef APP_H
#define APP_H

#include <QApplication>
#include "mainwindow.h"

#include "triggermanager/triggermanager.h"

class App : public QApplication
{
    Q_OBJECT
public:
    explicit App(int argc, char *argv[]);
    ~App();
signals:

public slots:

private:
    MainWindow *mMainWindow = nullptr;

    TriggerManager *triggerManager_ = new TriggerManager();
};

#endif // APP_H
