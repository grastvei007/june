#ifndef APP_H
#define APP_H

#include <QApplication>
#include "mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>

class App : public QApplication
{
    Q_OBJECT
public:
    explicit App(int argc, char *argv[]);
    ~App();
signals:

private slots:
    void onConnected();
    void onFinnished(QNetworkReply *reply);
private:
    MainWindow *mMainWindow = nullptr;
    QNetworkAccessManager networkAccessManager_;
    QNetworkRequestFactory networkRequestFactory_{{"http://localhost:5005/api"}};
};

#endif // APP_H
