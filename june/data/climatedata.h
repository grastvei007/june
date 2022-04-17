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

private slots:
    void onPowerTagSocketValueChanged(TagSocket *socket);
    void onFanTagSocketValueChanged(TagSocket *socket);
    void onHeatTagSocketValueChanged(TagSocket *socket);

private:
    std::unique_ptr<TagSocket> mPowerTagSocket;
    std::unique_ptr<TagSocket> mRunningTagSocket;
    std::unique_ptr<TagSocket> mFanTagSocket;
    std::unique_ptr<TagSocket> mHeatTagSocket;

    bool powerOn_ = false;
    int fanValue_ = 0;
    int heatValue_ = 0;
};

#endif // CLIMATEDATA_H
