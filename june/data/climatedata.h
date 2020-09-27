#ifndef CLIMATEDATA_H
#define CLIMATEDATA_H

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
    TagSocket *mPowerTagSocket;
    TagSocket *mRunningTagSocket;
    TagSocket *mFanTagSocket;
    TagSocket *mHeatTagSocket;

};

#endif // CLIMATEDATA_H
