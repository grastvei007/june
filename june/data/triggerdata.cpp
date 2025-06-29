#include "triggerdata.h"
#include <QStringList>

#include <QNetworkReply>
#include <QFile>
#include <optional>

#include <tagsystem/util/json.h>

TriggerData::TriggerData(QNetworkAccessManager &nam,
                         QNetworkRequestFactory &networkRequestFactory,
                         QObject *parent)
    : QObject(parent)
    , networkRequestFactory_(networkRequestFactory)
    , networkAccessManager_(nam)
{

}

void TriggerData::addTrigger(const Trigger &trigger)
{
    triggers_.push_back(trigger);
    emit triggerAdded(triggers_.size());
}


void TriggerData::createTrigger(TriggerType type,
                                const QString &triggerName,
                                const QString &watchTag,
                                double targetValue,
                                bool sendToServer)
{
    Trigger trigger(type, triggerName, watchTag, targetValue);
    addTrigger(trigger);
    if(sendToServer)
        sendTriggerToServer(trigger);
}

void TriggerData::createTrigger(TriggerType type,
                                const QString &triggerName,
                                const QString &watchTag,
                                int targetValue,
                                int duration,
                                bool sendToServer)
{
    Trigger trigger(type, triggerName, watchTag, targetValue, duration);
    addTrigger(trigger);
    if(sendToServer)
        sendTriggerToServer(trigger);
}

const Trigger& TriggerData::getTrigger(unsigned int index) const
{

    return triggers_.at(index);
}

int TriggerData::numberOfTriggers() const
{
    return triggers_.size();
}

QStringList TriggerData::triggerTypes() const
{
    return QStringList() << toString(TriggerType::TriggerEveryTimeAbove)
         << toString(TriggerType::TriggerEveryTimeBelow)
         << toString(TriggerType::TriggerOnTime)
         << toString(TriggerType::ScheduleOnDuration);
}

QString TriggerData::toString(TriggerType type) const
{
    switch(type)
    {
    case TriggerType::TriggerEveryTimeAbove:
        return "TriggerEveryTimeAbove";
    case TriggerType::TriggerEveryTimeBelow:
        return "TriggerEveryTimeBelow";
    case TriggerType::TriggerOnTime:
        return "TriggerOnTime";
    case TriggerType::ScheduleOnDuration:
        return "ScheduleOnDuration";
    }

    return {};
}

std::optional<TriggerType> TriggerData::fromString(const QString &type)
{
    if(type == "TriggerEveryTimeAbove")
        return TriggerType::TriggerEveryTimeAbove;
    else if(type == "TriggerEveryTimeBelow")
        return TriggerType::TriggerEveryTimeBelow;
    else if(type == "TriggerOnTime")
        return TriggerType::TriggerOnTime;
    else if (type == "ScheduleOnDuration")
        return TriggerType::ScheduleOnDuration;

    return std::nullopt;
}

void TriggerData::uplaodTriggerFile(const QString &filename)
{
    QFile file(filename);
    if (!file.exists())
        return;

    if (file.open(QIODevice::ReadOnly))
    {
        auto data = file.readAll();
        QNetworkReply *reply = networkAccessManager_.post(networkRequestFactory_.createRequest(
                                                              "/trigger/upload"),
                                                          data);
        connect(reply, &QNetworkReply::finished, this, &TriggerData::onFetchFromServerFinnished);
    }
}

void TriggerData::fetchFromServer()
{
    QNetworkReply *reply = networkAccessManager_.get(networkRequestFactory_.createRequest("/trigger/get"));
    connect(reply, &QNetworkReply::finished, this, &TriggerData::onFetchFromServerFinnished);
}


void TriggerData::sendTriggerToServer(const Trigger &trigger) const
{
    QJsonDocument document(trigger.toJson());
    networkAccessManager_.post(networkRequestFactory_.createRequest("/trigger/create"), document.toJson());
}

bool TriggerData::hasTrigger(const QString &triggerName) const
{
    const auto found = std::find_if(triggers_.begin(), triggers_.end(), [&triggerName](const auto &trigger){
        return trigger.triggerName() == triggerName;
    });
    return found != triggers_.end();
}

void TriggerData::onFetchFromServerFinnished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    auto triggers = util::json::byteArrayToJsonArray(reply->readAll());
    reply->deleteLater();

    if(!triggers.has_value())
        return;

    triggers_.clear();

    const QJsonArray array = triggers.value();
    for(const auto &ref : array)
    {
        const QJsonObject &trigger = ref.toObject();
        const QString triggerName = trigger.value("triggername").toString();
        if(triggerName.isEmpty() || hasTrigger(triggerName))
            continue;

        if(const auto type = fromApiString( trigger.value("type").toString()); type.has_value())
        {
            const QString subsystem = trigger.value("subsystem").toString();
            const QString name = trigger.value("name").toString();
            const QString watchTagName = QString("%1.%2").arg(subsystem, name);
            if(const auto triggerType = type.value(); triggerType == TriggerType::TriggerOnTime)
            {
                int triggerValue = trigger.value("triggervalue").toInt();
                int duration = trigger.value("duration").toInt();
                createTrigger(triggerType, triggerName, watchTagName, triggerValue, duration, false);
            }
            else if(triggerType == TriggerType::TriggerEveryTimeAbove || triggerType == TriggerType::TriggerEveryTimeBelow)
            {
                double triggerValue = trigger.value("triggervalue").toDouble();
                createTrigger(triggerType, triggerName, watchTagName, triggerValue, false);
            } else if (triggerType == TriggerType::ScheduleOnDuration)
            {
                int duration = trigger.value("duration").toInt();
                int startTime = trigger.value("starttime").toInt();
                createTrigger(triggerType, triggerName, watchTagName, startTime, duration, false);
            }
        }
    }
    emit dataReady();
}

std::optional<TriggerType> TriggerData::fromApiString(const QString &str) const
{
    if(str == "triggerAbove")
        return TriggerType::TriggerEveryTimeAbove;
    else if(str == "trigggerBelow")
        return TriggerType::TriggerEveryTimeBelow;
    else if(str == "triggerOnTime")
        return TriggerType::TriggerOnTime;
    else if (str == "scheduleOnDuration")
        return TriggerType::ScheduleOnDuration;

    return std::nullopt;
}
