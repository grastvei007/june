#include "app.h"


App::App(int argc, char *argv[]) : QApplication (argc, argv)
{
    mMainWindow = new MainWindow;
    mMainWindow->show();
}

App::~App()
{
    if(mMainWindow)
        delete mMainWindow;
}
