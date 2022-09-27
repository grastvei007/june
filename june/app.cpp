#include "app.h"

#include <QCommandLineParser>
#include <QSettings>
#include <QSize>

#include <tagsystem/taglist.h>
#include <tagsystem/tagsocketlist.h>


App::App(int argc, char *argv[]) : QApplication (argc, argv)
{
    mMainWindow = new MainWindow;

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

    TagList::sGetInstance().setClientName("june");
    if(!TagList::sGetInstance().tryToAutoConnect())
        TagList::sGetInstance().connectToServer(parser.value(serverIp), 5000);
}

App::~App()
{
    if(mMainWindow)
        delete mMainWindow;
}
