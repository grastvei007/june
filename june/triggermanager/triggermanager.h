#ifndef TRIGGERMANAGER_H
#define TRIGGERMANAGER_H

#include <map>
#include <vector>

#include <QString>

#include "trigger.h"


class TriggerManager
{
public:
    TriggerManager();

    void addTrigger(QString name, Trigger *trigger);

    int numberOfTriggers() const;
    Trigger* getTriggerByIndex(int index);

private:
    std::map<QString, Trigger*> triggers_;
    std::vector<Trigger*> triggersByIndex_;
};

#endif // TRIGGERMANAGER_H
