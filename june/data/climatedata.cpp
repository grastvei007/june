#include "climatedata.h"

ClimateData::ClimateData(QObject *parent) : QObject(parent)
{
    mPowerTagSocket.reset(TagSocket::createTagSocket("june", "heaterStart", TagSocket::eBool));
    mRunningTagSocket.reset(TagSocket::createTagSocket("june", "heaterRunning", TagSocket::eBool));
    mFanTagSocket.reset(TagSocket::createTagSocket("june", "heaterFan", TagSocket::eInt));
    mHeatTagSocket.reset(TagSocket::createTagSocket("june", "heaterHeat", TagSocket::eInt));

    mPowerTagSocket->hookupTag("heater", "start");
    mRunningTagSocket->hookupTag("heater", "on");
    mFanTagSocket->hookupTag("heater", "fan");
    mHeatTagSocket->hookupTag("heater", "effect");
}

void ClimateData::setPower(bool aPower)
{
    mPowerTagSocket->writeValue(aPower);
}

void ClimateData::setRunning(bool aOn)
{
    mRunningTagSocket->writeValue(aOn);
}

void ClimateData::setFan(int aValue)
{
    mFanTagSocket->writeValue(aValue);
}

void ClimateData::setHeat(int aValue)
{
    mHeatTagSocket->writeValue(aValue);
}
