#include "app.h"

#include <tagsystem/taglist.h>

App::App(int argc, char *argv[]) : QApplication(argc, argv)
{
    mSystemTrayIcon = new SystemTrayIcon();

    TagList::sGetInstance().setClientName("BatteryMonitor");
    TagList::sGetInstance().connectToServer("localhost", 5000);
    TagList::sGetInstance().setAutoconnectOnBroadcast(true);
}
