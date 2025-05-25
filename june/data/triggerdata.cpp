#include "triggerdata.h"

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

const Trigger& TriggerData::getTrigger(unsigned int index) const
{

    return triggers_.at(index);
}

int TriggerData::numberOfTriggers() const
{
    return triggers_.size();
}

