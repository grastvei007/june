#include "triggermanager.h"

TriggerManager::TriggerManager()
{

}

void TriggerManager::addTrigger(QString name, Trigger *trigger)
{

    if(triggers_.count(name))
    {
        triggersByIndex_.push_back(trigger);
    }
    triggers_[name] = trigger;
}

int TriggerManager::numberOfTriggers() const
{
    return triggers_.size();
}

Trigger *TriggerManager::getTriggerByIndex(int index)
{
    if(triggersByIndex_.empty())
        return nullptr;
    return triggersByIndex_.at(index);
}
