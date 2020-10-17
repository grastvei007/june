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

    mPiFanTagSocket.reset(TagSocket::createTagSocket("june", "piFan", TagSocket::eInt));
    mPiHeatTagSocket.reset(TagSocket::createTagSocket("june", "piHeat", TagSocket::eInt));

    mPiFanTagSocket->hookupTag("raspberrypi", "fan");
    mPiHeatTagSocket->hookupTag("raspberrypi", "effect");

    connect(mPiFanTagSocket.get(), qOverload<int>(&TagSocket::valueChanged), this, &ClimateData::onPiFanTagSocketValueChanged);
    connect(mPiHeatTagSocket.get(), qOverload<int>(&TagSocket::valueChanged), this, &ClimateData::onPiHeatTagSocketValueChanged);
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

void ClimateData::onPiFanTagSocketValueChanged(int aValue)
{
    int value = aValue/10;
    if(value != mFanValue)
    {
        mFanValue = value;
        emit fanValueChanged(value);
    }
}

void ClimateData::onPiHeatTagSocketValueChanged(int aValue)
{
    int value = aValue/10;
    if(value != mHeatValue)
    {
        mHeatValue = value;
        emit heatValueChanged(value);
    }
}
