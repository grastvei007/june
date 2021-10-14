#include "trigger.h"

Trigger::Trigger(const QString &name) : name_(name)
{

}

const QString &Trigger::name() const
{
    return name_;
}

bool Trigger::isActive() const
{
    return isActive_;
}
