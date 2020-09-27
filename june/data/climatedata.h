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

private:
    std::unique_ptr<TagSocket> mPowerTagSocket;
    std::unique_ptr<TagSocket> mRunningTagSocket;
    std::unique_ptr<TagSocket> mFanTagSocket;
    std::unique_ptr<TagSocket> mHeatTagSocket;

};

#endif // CLIMATEDATA_H
