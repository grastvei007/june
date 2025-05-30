#ifndef TRIGGER_H
#define TRIGGER_H

#include <QString>
#include <QJsonObject>

enum class TriggerType;

class Trigger
{
public:
    Trigger(TriggerType type, const QString &triggerName, const QString &watchTag, double targetValue);
    Trigger(TriggerType type, const QString &triggerName, const QString &watchTag, int targetValue, int duration);

    QJsonObject toJson() const;

    TriggerType triggerType() const;
    const QString& triggerName() const;
    const QString& watchTag() const;
    double targetValued() const;
    int targetValuei() const;
    int duration() const;
private:
    QString typeToApiString(TriggerType type) const;
    TriggerType type_;
    QString triggerName_;
    QString watchTag_;
    double targetValued_ = 0.0;
    int targetValuei_ = 0;
    int duration_ = 0;
};

#endif // TRIGGER_H
