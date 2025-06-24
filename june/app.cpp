#include "app.h"

#include <QCommandLineParser>
#include <QSettings>
#include <QSize>

#include <tagsystem/taglist.h>
#include <tagsystem/tagsocketlist.h>

#include <QString>
#include <QNetworkReply>
#include <QUrl>

#include "data/triggerdata.h"
#include "data/climatedata.h"
#include "data/pigpiodata.h"

#include "gui/triggerguiwidget.h"
#include "gui/climateguiwidget.h"
#include "gui/pigpiowidget.h"

App::App(int argc, char *argv[]) :
    networkAccessManager_(),
    QApplication (argc, argv)
{
    QSettings settings("June", "June");
    QSize size =  settings.value("mainwindow/size").toSize();


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
    TagSocketList::sGetInstance().setAutoSave();

    connect(&TagList::sGetInstance(), &TagList::connected, this, &App::onConnected);
    connect(&networkAccessManager_, &QNetworkAccessManager::finished, this, &App::onFinnished);

    TagList::sGetInstance().setClientName("june");
    if(!TagList::sGetInstance().tryToAutoConnect())
        TagList::sGetInstance().connectToServer(parser.value(serverIp), 5000);

    triggerData_ = std::make_unique<TriggerData>(networkAccessManager_, networkRequestFactory_);
    climateData_ = std::make_unique<ClimateData>(this);
    piGpioData_ = std::make_unique<PiGpioData>(networkAccessManager_, networkRequestFactory_);

    centralWidgetFactory_.add<TriggerGuiWidget, TriggerData>("Triggers", triggerData_.get());
    centralWidgetFactory_.add<ClimateGuiWidget, ClimateData>("Climate", climateData_.get());
    centralWidgetFactory_.add<PiGpioWidget, PiGpioData>("pi-gpio", piGpioData_.get());

    mMainWindow = new MainWindow(centralWidgetFactory_, networkAccessManager_, networkRequestFactory_);
    if(size.isValid())
        mMainWindow->resize(size);

    mMainWindow->show();
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

    qDebug() << "Api adress changes: " << QString("http://%1:%2/api").arg(adress, QString::number(port));

    networkRequestFactory_.setBaseUrl(QUrl(QString("http://%1:%2/api").arg(adress, QString::number(port))));
}

void App::onFinnished(QNetworkReply *reply)
{
    if(reply->error())
        qDebug() << reply->errorString();
}
