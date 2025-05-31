#include "trigger.h"

#include "triggerdata.h"

Trigger::Trigger(TriggerType type,
                 const QString &triggerName,
                 const QString &watchTag,
                 double targetValue) :
    type_(type),
    triggerName_(triggerName),
    watchTag_(watchTag),
    targetValued_(targetValue)
{

}

Trigger::Trigger(TriggerType type,
                 const QString &triggerName,
                 const QString &watchTag,
                 int targetValue,
                 int duration) :
    type_(type),
    triggerName_(triggerName),
    watchTag_(watchTag),
    targetValuei_(targetValue),
    duration_(duration)
{

}

QJsonObject Trigger::toJson() const
{
    auto subsystem = watchTag_.split(".").first();
    auto name = watchTag_.split(".").last();

    QJsonObject obj;
    obj.insert("type", typeToApiString(type_));
    obj.insert("subsystem", subsystem);
    obj.insert("name", name);
    obj.insert("triggername", triggerName_);

    if(type_ == TriggerType::TriggerEveryTimeAbove || type_ == TriggerType::TriggerEveryTimeBelow)
    {
        obj.insert("triggervalue", targetValued_);
    }
    else if(type_ == TriggerType::TriggerOnTime)
    {
        obj.insert("triggervalue", targetValuei_);
        obj.insert("duration", duration_);
    }

    return obj;
}

TriggerType Trigger::triggerType() const
{
    return type_;
}

const QString &Trigger::triggerName() const
{
    return triggerName_;
}

const QString &Trigger::watchTag() const
{
    return watchTag_;
}

double Trigger::targetValued() const
{
    return targetValued_;
}

int Trigger::targetValuei() const
{
    return targetValuei_;
}

int Trigger::duration() const
{
    return duration_;
}

QString Trigger::typeToApiString(TriggerType type) const
{
    switch(type)
    {
    case TriggerType::TriggerEveryTimeAbove:
        return "triggerAbove";
    case TriggerType::TriggerEveryTimeBelow:
        return "trigggerBelow";
    case TriggerType::TriggerOnTime:
        return "triggerOnTime";
    }

    return {};
}
