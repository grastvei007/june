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

Trigger::Trigger(const QJsonObject &obj)
{
    triggerName_ = obj.value("triggername").toString();

    const QString subsystem = obj.value("subsystem").toString();
    const QString name = obj.value("name").toString();
    watchTag_ = QString("%1.%2").arg(subsystem, name);
    type_ = fromApiString(obj.value("type").toString()).value();
    isEnabled_ = obj.value("enable").toBool();

    if(type_ == TriggerType::TriggerOnTime)
    {
        targetValuei_ = obj.value("triggervalue").toInt();
        duration_ = obj.value("duration").toInt();
    }
    else if(type_ == TriggerType::TriggerEveryTimeAbove || type_ == TriggerType::TriggerEveryTimeBelow)
    {
        targetValued_ = obj.value("triggervalue").toDouble();
    }
    else if (type_ == TriggerType::ScheduleOnDuration)
    {
        duration_ = obj.value("duration").toInt();
        targetValuei_ = obj.value("starttime").toInt();
    }
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
    obj.insert("enable", isEnabled_);

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

bool Trigger::isEnabled() const
{
    return isEnabled_;
}

std::optional<TriggerType> Trigger::fromApiString(const QString &type)
{
    if(type == "triggerAbove")
        return TriggerType::TriggerEveryTimeAbove;
    else if(type == "trigggerBelow")
        return TriggerType::TriggerEveryTimeBelow;
    else if(type == "triggerOnTime")
        return TriggerType::TriggerOnTime;
    else if (type == "scheduleOnDuration")
        return TriggerType::ScheduleOnDuration;

    return std::nullopt;
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
    case TriggerType::ScheduleOnDuration:
        return "scheduleOnDuration";
    }

    return {};
}
