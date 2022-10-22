#include "climatedata.h"

ClimateData::ClimateData(QObject *parent) : QObject(parent)
{
    mPowerTagSocket.reset(TagSocket::createTagSocket("june", "heaterStart", TagSocket::eBool));
    mRunningTagSocket.reset(TagSocket::createTagSocket("june", "heaterRunning", TagSocket::eBool));
    mFanTagSocket.reset(TagSocket::createTagSocket("june", "heaterFan", TagSocket::eInt));
    mHeatTagSocket.reset(TagSocket::createTagSocket("june", "heaterHeat", TagSocket::eInt));

    temperatureInsideTagSocket_.reset(TagSocket::createTagSocket("june", "temperatureInside", TagSocket::eDouble));
    temperatureOutdoorTagSocket_.reset(TagSocket::createTagSocket("june", "temperatureOutdoor", TagSocket::eDouble));

    if(!mPowerTagSocket->isHookedUp() || !mPowerTagSocket->isWaitingForTag())
        mPowerTagSocket->hookupTag("heater", "start");
    if(!mRunningTagSocket->isHookedUp() || !mRunningTagSocket->isWaitingForTag())
        mRunningTagSocket->hookupTag("heater", "on");
    if(!mFanTagSocket->isHookedUp() || !mFanTagSocket->isWaitingForTag())
        mFanTagSocket->hookupTag("heater", "fan");
    if(!mHeatTagSocket->isHookedUp() || !mHeatTagSocket->isWaitingForTag())
        mHeatTagSocket->hookupTag("heater", "effect");
    if(!temperatureInsideTagSocket_->isHookedUp() || !temperatureInsideTagSocket_->isWaitingForTag())
        temperatureInsideTagSocket_->hookupTag("temperature", "indoor");
    if(!temperatureOutdoorTagSocket_->isHookedUp() || !temperatureOutdoorTagSocket_->isWaitingForTag())
        temperatureOutdoorTagSocket_->hookupTag("temperature", "outside");

    connect(mPowerTagSocket.get(), qOverload<TagSocket*>(&TagSocket::valueChanged), this, &ClimateData::onPowerTagSocketValueChanged);
    connect(mFanTagSocket.get(), qOverload<TagSocket*>(&TagSocket::valueChanged), this, &ClimateData::onFanTagSocketValueChanged);
    connect(mHeatTagSocket.get(), qOverload<TagSocket*>(&TagSocket::valueChanged), this, &ClimateData::onHeatTagSocketValueChanged);

    connect(temperatureInsideTagSocket_.get(), qOverload<TagSocket*>(&TagSocket::valueChanged), this, &ClimateData::onTemperatureInsideValueChanged);
    connect(temperatureOutdoorTagSocket_.get(), qOverload<TagSocket*>(&TagSocket::valueChanged), this, &ClimateData::onTemperatureOutsideValueChange);

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

void ClimateData::onTemperatureInsideValueChanged(TagSocket *socket)
{
    double value;
    if(!socket->readValue(value))
        return;
     if(value == temperatureInside_)
         return;
     temperatureInside_ = value;
     emit temeratureInsideValueChange(temperatureInside_);
}

void ClimateData::onTemperatureOutsideValueChange(TagSocket *socket)
{
    double value;
    if(!socket->readValue(value))
        return;
    if(value == temperatureOutdoor_)
        return;
    temperatureOutdoor_ = value;
    emit temperaturOutdoorValueChange(temperatureOutdoor_);
}
