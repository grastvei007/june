#include "triggerdata.h"
#include <QStringList>

TriggerData::TriggerData(QNetworkAccessManager &nam,
                         QNetworkRequestFactory &networkRequestFactory,
                         QObject *parent)
    : QObject(parent)
    , networkRequestFactory_(networkRequestFactory)
    , networkAccessManager_(nam)
{

}

void TriggerData::addTrigger(const Trigger &trigger)
{
    triggers_.push_back(trigger);
    emit triggerAdded(triggers_.size());
}

void TriggerData::createTrigger(TriggerType type,
                                const QString &triggerName,
                                const QString &watchTag,
                                double targetValue)
{

}

void TriggerData::createTrigger(TriggerType type,
                                const QString &triggerName,
                                const QString &watchTag,
                                int targetValue,
                                int duration)
{

}

const Trigger& TriggerData::getTrigger(unsigned int index) const
{

    return triggers_.at(index);
}

int TriggerData::numberOfTriggers() const
{
    return triggers_.size();
}

QStringList TriggerData::triggerTypes() const
{
    return QStringList() << toString(TriggerType::TriggerEveryTimeAbove)
         << toString(TriggerType::TriggerEveryTimeBelow)
         << toString(TriggerType::TriggerOnTime);
}

QString TriggerData::toString(TriggerType type) const
{
    switch(type)
    {
    case TriggerType::TriggerEveryTimeAbove:
        return "TriggerEveryTimeAbove";
    case TriggerType::TriggerEveryTimeBelow:
        return "TriggerEveryTimeBelow";
    case TriggerType::TriggerOnTime:
        return "TriggerOnTime";
    }

    return {};
}

std::optional<TriggerType> TriggerData::fromString(const QString &type)
{
    if(type == "TriggerEveryTimeAbove")
        return TriggerType::TriggerEveryTimeAbove;
    else if(type == "TriggerEveryTimeBelow")
        return TriggerType::TriggerEveryTimeBelow;
    else if(type == "TriggerOnTime")
        return TriggerType::TriggerOnTime;

    return std::nullopt;
}
