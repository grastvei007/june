#ifndef APP_H
#define APP_H

#include <QApplication>
#include "mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>

#include "gui/centralwidgetfactory.h"

class TriggerData;
class ClimateData;
class PiGpioData;
class TagSocketBindingData;
class LogValueData;
class FarmingData;

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

    CentralWiddgetFactory centralWidgetFactory_ = {};

    std::unique_ptr<TriggerData> triggerData_;
    std::unique_ptr<ClimateData> climateData_;
    std::unique_ptr<PiGpioData> piGpioData_;
    std::unique_ptr<TagSocketBindingData> tagSocketBindingData_;
    std::unique_ptr<LogValueData> logValueData_;
    std::unique_ptr<FarmingData> farmingData_;
};

#endif // APP_H
