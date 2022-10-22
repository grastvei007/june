#ifndef CLIMATEDATA_H
#define CLIMATEDATA_H

#include <memory>

#include <QObject>

#include <tagsystem/tagsocket.h>

class ClimateData : public QObject
{
    Q_OBJECT
public:
    explicit ClimateData(QObject *parent = nullptr);

    void setPower(bool aPower);
    void setRunning(bool aOn);
    void setFan(int aValue);
    void setHeat(int aValue);
signals:
    void powerOnValueChanged(bool);
    void fanValueChanged(int);
    void heatValueChanged(int);
    void temeratureInsideValueChange(double);
    void temperaturOutdoorValueChange(double);

private slots:
    void onPowerTagSocketValueChanged(TagSocket *socket);
    void onFanTagSocketValueChanged(TagSocket *socket);
    void onHeatTagSocketValueChanged(TagSocket *socket);

    void onTemperatureInsideValueChanged(TagSocket *socket);
    void onTemperatureOutsideValueChange(TagSocket *socket);

private:
    std::unique_ptr<TagSocket> mPowerTagSocket;
    std::unique_ptr<TagSocket> mRunningTagSocket;
    std::unique_ptr<TagSocket> mFanTagSocket;
    std::unique_ptr<TagSocket> mHeatTagSocket;

    std::unique_ptr<TagSocket> temperatureInsideTagSocket_;
    std::unique_ptr<TagSocket> temperatureOutdoorTagSocket_;

    bool powerOn_ = false;
    int fanValue_ = 0;
    int heatValue_ = 0;

    double temperatureInside_ = 0.0;
    double temperatureOutdoor_ = 0.0;
};

#endif // CLIMATEDATA_H
