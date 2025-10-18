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
    TriggerOnTime,
    ScheduleOnDuration,
    TriggerTwoValues
};

enum class TwoValueTrigger
{
    TriggerAboveValue,
    TriggerBelowValue
};

class Trigger;

class TriggerData : public QObject
{
    Q_OBJECT
public:
    explicit TriggerData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent = nullptr);

    void addTrigger(const Trigger &trigger);
    void createTrigger(TriggerType type, const QString &triggerName, const QString &watchTag, double targetValue, bool sendToServer=true);
    void createTrigger(TriggerType type, const QString &triggerName, const QString &watchTag, int targetValue, int duration, bool sendToServer=true);

    const Trigger& getTrigger(unsigned int index) const;
    int numberOfTriggers() const;
    QStringList triggerTypes() const;
    QString toString(TriggerType type) const;
    std::optional<TriggerType> fromString(const QString &type);

    void uplaodTriggerFile(const QString &filename);
    void removeTrigger(const QString &triggerName);

    void fetchFromServer();
signals:
    void triggerAdded(int index);
    void dataReady();

private slots:
    void onFetchFromServerFinnished();

private:
    void sendTriggerToServer(const Trigger &trigger) const;
    bool hasTrigger(const QString &triggerName) const;

    std::vector<Trigger> triggers_;
    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;
};


#endif // TRIGGERDATA_H
