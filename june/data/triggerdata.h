#ifndef TRIGGERDATA_H
#define TRIGGERDATA_H

#include <vector>
#include <optional>

#include <QObject>
#include <QNetworkRequestFactory>
#include <QNetworkAccessManager>

#include "trigger.h"

enum class TriggerType
{
    TriggerEveryTimeAbove,
    TriggerEveryTimeBelow,
    TriggerOnTime
};

class TriggerData : public QObject
{
    Q_OBJECT
public:
    explicit TriggerData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent = nullptr);

    void addTrigger(const Trigger &trigger);
    void createTrigger(TriggerType type, const QString &triggerName, const QString &watchTag, double targetValue);
    void createTrigger(TriggerType type, const QString &triggerName, const QString &watchTag, int targetValue, int duration);

    const Trigger& getTrigger(unsigned int index) const;
    int numberOfTriggers() const;
    QStringList triggerTypes() const;
    QString toString(TriggerType type) const;
    std::optional<TriggerType> fromString(const QString &type);
signals:
    void triggerAdded(int index);

private:
    std::vector<Trigger> triggers_;
    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;
};


#endif // TRIGGERDATA_H
