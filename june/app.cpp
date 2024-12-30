#include "app.h"

#include <QCommandLineParser>
#include <QSettings>
#include <QSize>

#include <tagsystem/taglist.h>
#include <tagsystem/tagsocketlist.h>

#include <QString>
#include <QNetworkReply>
#include <QUrl>

App::App(int argc, char *argv[]) :
    networkAccessManager_(),
    QApplication (argc, argv)
{
    mMainWindow = new MainWindow(networkAccessManager_, networkRequestFactory_);

    QSettings settings("June", "June");
    QSize size =  settings.value("mainwindow/size").toSize();
    if(size.isValid())
        mMainWindow->resize(size);

    mMainWindow->show();

    QCommandLineParser parser;
    parser.setApplicationDescription("Pi client to map the gpio to a june server, and manipulate the values over local network");
    parser.addVersionOption();
    parser.addHelpOption();

    QCommandLineOption serverIp("ip", "server-ip", "Connect to server");
    serverIp.setDefaultValue("localhost");
    parser.addOption(serverIp);

    parser.process(*this);

    TagSocketList::sGetInstance().setApplicationName("june");
    TagSocketList::sGetInstance().loadBindingList();

    connect(&TagList::sGetInstance(), &TagList::connected, this, &App::onConnected);
    connect(&networkAccessManager_, &QNetworkAccessManager::finished, this, &App::onFinnished);

    TagList::sGetInstance().setClientName("june");
    if(!TagList::sGetInstance().tryToAutoConnect())
        TagList::sGetInstance().connectToServer(parser.value(serverIp), 5000);
}

App::~App()
{
    if(mMainWindow)
        delete mMainWindow;
}

void App::onConnected()
{
    const auto adress = TagList::sGetInstance().adress();
    const int port = 5005; // api port

    networkRequestFactory_.setBaseUrl(QUrl(QString("http://%1:%2/api").arg(adress, port)));
}

void App::onFinnished(QNetworkReply *reply)
{
    if(reply->error())
        qDebug() << reply->errorString();
    else
        qDebug() << reply->readAll();
}
