#include "triggerdata.h"

TriggerData::TriggerData(QObject *parent) : QObject(parent)
{

}

void TriggerData::addTrigger(std::any trigger)
{
    triggers_.push_back(trigger);
    emit triggerAdded(triggers_.size());
}

std::optional<std::any> TriggerData::getTrigger(int index)
{
    if (index < 0 || index > (int) triggers_.size())
        return std::nullopt;

    return triggers_.at(index);
}

int TriggerData::numberOfTriggers() const
{
    return triggers_.size();
}

