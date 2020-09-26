#include "app.h"

#include <QCommandLineParser>

#include <tagsystem/taglist.h>

App::App(int argc, char *argv[]) : QApplication(argc, argv)
{
    setOrganizationName("MySoft");
    setOrganizationDomain("mysoft.com");
    setApplicationName("Battery Monitor");
    setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Brings serial port devices to june. \n Default serial port values:\n baudrate 9600 \n databits 8 \n no parity \n one stop bit \n no flow control\n");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption gui(QStringList() << "s" << "system_bar", "System bar");
    parser.addOption(gui);

    QCommandLineOption serverIp("ip", "server-ip", "Connect to server");
    serverIp.setDefaultValue("localhost");
    parser.addOption(serverIp);


    parser.process(*this);

    mSystemTrayIcon = new SystemTrayIcon();

    TagList::sGetInstance().setClientName("BatteryMonitor");
    TagList::sGetInstance().connectToServer(parser.value(serverIp), 5000);
    TagList::sGetInstance().setAutoconnectOnBroadcast(true);
}
