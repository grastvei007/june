#ifndef TRIGGER_H
#define TRIGGER_H

#include <QString>
#include <QJsonObject>

enum class TriggerType;
enum class TwoValueTrigger;

struct TwoValueTriggerPair
{
    TwoValueTrigger rule;
    double value;
};

class Trigger
{
public:
    Trigger(TriggerType type, const QString &triggerName, const QString &watchTag, double targetValue);
    Trigger(TriggerType type, const QString &triggerName, const QString &watchTag, int targetValue, int duration);
    Trigger(TriggerType type,
            const QString &triggerName,
            const QString &watchTag,
            TwoValueTriggerPair on, TwoValueTriggerPair off);
    Trigger(const QJsonObject &obj);

    QJsonObject toJson() const;

    TriggerType triggerType() const;
    const QString& triggerName() const;
    const QString& watchTag() const;
    double targetValued() const;
    int targetValuei() const;
    int duration() const;
    bool isEnabled() const;

    TwoValueTriggerPair onValue() const;
    TwoValueTriggerPair offValue() const;

    void setWatchTag(const QString &watchTag);
    void setEnable(bool enable);
    void setTwoValueTrigger(double on, double off);
    void setTargetValue(int target);
    void setDuration(int duration);

    static std::optional<TriggerType> fromApiString(const QString &type);
private:
    QString typeToApiString(TriggerType type) const;
    TriggerType type_;
    QString triggerName_;
    QString watchTag_;
    double targetValued_ = 0.0;
    int targetValuei_ = 0;
    int duration_ = 0;
    bool isEnabled_ = true;

    TwoValueTriggerPair triggerOnValue_;
    TwoValueTriggerPair triggerOffValue_;
};

#endif // TRIGGER_H
