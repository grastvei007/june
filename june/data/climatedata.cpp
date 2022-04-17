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

    connect(mPowerTagSocket.get(), qOverload<TagSocket*>(&TagSocket::valueChanged), this, &ClimateData::onPowerTagSocketValueChanged);
    connect(mFanTagSocket.get(), qOverload<TagSocket*>(&TagSocket::valueChanged), this, &ClimateData::onFanTagSocketValueChanged);
    connect(mHeatTagSocket.get(), qOverload<TagSocket*>(&TagSocket::valueChanged), this, &ClimateData::onHeatTagSocketValueChanged);
}

void ClimateData::setPower(bool aPower)
{
    if(aPower == powerOn_)
        return;
    powerOn_ = aPower;
    mPowerTagSocket->writeValue(aPower);
    emit powerOnValueChanged(powerOn_);
}

void ClimateData::setRunning(bool aOn)
{
    mRunningTagSocket->writeValue(aOn);
}

void ClimateData::setFan(int value)
{
    if(value == fanValue_)
        return;
    fanValue_ = value;
    mFanTagSocket->writeValue(value);
    emit fanValueChanged(fanValue_);
}

void ClimateData::setHeat(int value)
{
    if(value == heatValue_)
        return;
    heatValue_ = value;
    mHeatTagSocket->writeValue(value);
    emit heatValueChanged(heatValue_);
}

void ClimateData::onPowerTagSocketValueChanged(TagSocket *socket)
{
    bool value;
    if(socket->readValue(value))
        setPower(value);
}

void ClimateData::onFanTagSocketValueChanged(TagSocket *socket)
{
    int value;
    if(socket->readValue(value))
        setFan(value);

}

void ClimateData::onHeatTagSocketValueChanged(TagSocket *socket)
{
    int value;
    if(socket->readValue(value))
        setHeat(value);
}
