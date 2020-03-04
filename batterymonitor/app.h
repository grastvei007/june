#ifndef APP_H
#define APP_H

#include <QApplication>

#include "systemtrayicon.h"

class App : public QApplication
{
    Q_OBJECT
public:
    App(int argc, char *argv[]);

signals:

public slots:

private:
    SystemTrayIcon *mSystemTrayIcon;
};

#endif // APP_H
