#ifndef APP_H
#define APP_H

#include <QApplication>
#include "mainwindow.h"
#include <QNetworkAccessManager>

class App : public QApplication
{
    Q_OBJECT
public:
    explicit App(int argc, char *argv[]);
    ~App();
signals:

private slots:
    void onConnected();
private:
    MainWindow *mMainWindow = nullptr;
    QNetworkAccessManager networkAccessManager_;
};

#endif // APP_H
