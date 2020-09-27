#include "app.h"

#include <QCommandLineParser>

#include <tagsystem/taglist.h>
#include <tagsystem/tagsocketlist.h>


App::App(int argc, char *argv[]) : QApplication (argc, argv)
{
    mMainWindow = new MainWindow;
    mMainWindow->show();

    QCommandLineParser parser;
    parser.setApplicationDescription("Pi client to map the gpio to a june server, and manipulate the values over local network");
    parser.addVersionOption();
    parser.addHelpOption();

    QCommandLineOption serverIp("ip", "server-ip", "Connect to server");
    serverIp.setDefaultValue("localhost");
    parser.addOption(serverIp);

    parser.process(*this);

//    TagSocketList::sGetInstance().setApplicationName("june");
//    TagSocketList::sGetInstance().loadBindingList();

    TagList::sGetInstance().setClientName("june");
    TagList::sGetInstance().connectToServer(parser.value(serverIp), 5000);
}

App::~App()
{
    if(mMainWindow)
        delete mMainWindow;
}
