#include "app.h"

#include <QCommandLineParser>
#include <QSettings>
#include <QSize>

#include <tagsystem/taglist.h>
#include <tagsystem/tagsocketlist.h>


App::App(int argc, char *argv[]) :
    networkAccessManager_(),
    QApplication (argc, argv)
{
    mMainWindow = new MainWindow(networkAccessManager_);

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
    networkAccessManager_.disconnect();
    networkAccessManager_.connectToHost(adress, port);
    qDebug() << "connected to api " << adress <<":" << port;
}
