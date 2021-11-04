#include "climatedata.h"

ClimateData::ClimateData(QObject *parent) : QObject(parent)
{
    mPowerTagSocket.reset(TagSocket::createTagSocket("june", "heaterStart", TagSocket::eBool));
    mRunningTagSocket.reset(TagSocket::createTagSocket("june", "heaterRunning", TagSocket::eBool));
    mFanTagSocket.reset(TagSocket::createTagSocket("june", "heaterFan", TagSocket::eInt));
    mHeatTagSocket.reset(TagSocket::createTagSocket("june", "heaterHeat", TagSocket::eInt));

    if(!mPowerTagSocket->isHookedUp() || !mPowerTagSocket->isWaitingForTag())
        mPowerTagSocket->hookupTag("heater", "start");
    if(!mRunningTagSocket->isHookedUp() || !mRunningTagSocket->isWaitingForTag())
        mRunningTagSocket->hookupTag("heater", "on");
    if(!mFanTagSocket->isHookedUp() || !mFanTagSocket->isWaitingForTag())
        mFanTagSocket->hookupTag("heater", "fan");
    if(!mHeatTagSocket->isHookedUp() || !mHeatTagSocket->isWaitingForTag())
        mHeatTagSocket->hookupTag("heater", "effect");

    mPiFanTagSocket.reset(TagSocket::createTagSocket("june", "piFan", TagSocket::eInt));
    mPiHeatTagSocket.reset(TagSocket::createTagSocket("june", "piHeat", TagSocket::eInt));

    if(!mPiFanTagSocket->isHookedUp() || !mPiFanTagSocket->isWaitingForTag())
        mPiFanTagSocket->hookupTag("raspberrypi", "fan");
    if(mPiHeatTagSocket->isHookedUp() || !mPiHeatTagSocket->isWaitingForTag())
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
