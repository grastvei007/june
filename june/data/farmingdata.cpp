#include "farmingdata.h"

#include <ranges>

#include <QJsonObject>
#include <QNetworkReply>

#include <tagsystem/util/json.h>
#include <tagsystem/taglist.h>
#include <tagsystem/util/tagutil.h>

FarmingData::FarmingData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent) :
    networkRequestFactory_(networkRequestFactory),
    networkAccessManager_(nam),
    QObject(parent)
{
    // triggers that control the farming, they should be fetched from server,
    // but are created if not existing
    triggerSet_.push_back(QString("seedheating"));
    triggerSet_.push_back(QString("growlighton"));
}

void FarmingData::fetchFromServer()
{
    auto requestArray = createRequestArray();
    QJsonDocument doc(requestArray);

    QNetworkReply *reply = networkAccessManager_.post(networkRequestFactory_.createRequest(
                                                          "/trigger/get"),
                                                      doc.toJson());
    connect(reply, &QNetworkReply::finished, this, &FarmingData::onFetchFromServerFinnished);
}

double FarmingData::seedHeatingOn() const
{
    for (const auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                                   return e.triggerName() == "seedheating";
                               }))
    {
        return trigger.onValue().value;
    }
    qWarning() << "Invalid seed heating on value";
    return 0.0;
}

double FarmingData::seedHeatingOff() const
{
    for (const auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                                   return e.triggerName() == "seedheating";
                               }))
    {
        return trigger.offValue().value;
    }
    qWarning() << "Invalid seed heating off value";
    return 0.0;
}

QString FarmingData::seedWatchTag() const
{
    for (const auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                                   return e.triggerName() == "seedheating";
                               }))
    {
        return trigger.watchTag();
    }

    return {};
}

QString FarmingData::seedTemperatureSensor() const
{
    QString tagName = seedWatchTag();
    if (tagName.isEmpty())
        return {};
    auto [subystem, name] = util::tag::splitFullName(tagName);
    return name;
}

bool FarmingData::isSeedHeatingEnabled() const
{
    for (const auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                                   return e.triggerName() == "seedheating";
                               }))
    {
        return trigger.isEnabled();
    }
    return false;
}

QTime FarmingData::turnOnGrowLight() const
{
    for (const auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                                   return e.triggerName() == "growlighton";
                               }))
    {
        int target = trigger.targetValuei();
        return QTime::fromMSecsSinceStartOfDay(target);
    }
    return QTime(7, 0, 0); // default value
}

QTime FarmingData::turnOffGrowLight() const
{
    for (const auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                                   return e.triggerName() == "growlighton";
                               }))
    {
        int target = trigger.targetValuei();
        int durationMs = trigger.duration();

        return QTime::fromMSecsSinceStartOfDay(target + durationMs);
    }
    return QTime(19, 0, 0); // default value
}

bool FarmingData::isTurnOffGrowLightEnabled() const
{
    for (const auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                                   return e.triggerName() == "growlighton";
                               }))
    {
        return trigger.isEnabled();
    }
    return false;
}

QStringList FarmingData::availableTemperatureSensors() const
{
    QStringList result;
    auto temperatureSensorTags = TagList::sGetInstance().findTagsInSubsystem("temperature");
    for (auto *tag : temperatureSensorTags)
    {
        result.push_back(tag->getName());
    }

    return result;
}

void FarmingData::setTemperatureSensor(const QString &sensor)
{
    auto tagName = util::tag::fullName("temperature", sensor);

    for (auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                             return e.triggerName() == "seedheating";
                         }))
    {
        trigger.setWatchTag(tagName);
    }
}

void FarmingData::setTempeperature(double temperature)
{
    for (auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                             return e.triggerName() == "seedheating";
                         }))
    {
        trigger.setTwoValueTrigger(temperature - temperatureDelta_, temperature + temperatureDelta_);
    }
}

void FarmingData::enableSeedControl(bool enable)
{
    for (auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                             return e.triggerName() == "seedheating";
                         }))
    {
        trigger.setEnable(enable);
    }
}

void FarmingData::enableGrowLight(bool enable)
{
    for (auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                             return e.triggerName() == "growlighton";
                         }))
    {
        trigger.setEnable(enable);
    }
}

void FarmingData::setGrowLigtTime(int startTime, int duration)
{
    for (auto &trigger : triggers_ | std::views::filter([](const auto &e) {
                             return e.triggerName() == "growlighton";
                         }))
    {
        trigger.setTargetValue(startTime);
        trigger.setDuration(duration);
    }
}

void FarmingData::sendToServer()
{
    QJsonArray array;
    for (const auto &trigger : triggers_)
    {
        array.push_back(trigger.toJson());
    }
    QJsonDocument doc(array);

    if (triggersExistOnServer_)
    {
        QNetworkReply *reply = networkAccessManager_.post(networkRequestFactory_.createRequest(
                                                              "/trigger/update"),
                                                          doc.toJson());
    } else
    {
        QNetworkReply *reply = networkAccessManager_.post(networkRequestFactory_.createRequest(
                                                              "/trigger/create"),
                                                          doc.toJson());
        triggersExistOnServer_ = true;
    }
}

void FarmingData::onFetchFromServerFinnished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    auto triggers = util::json::byteArrayToJsonArray(reply->readAll());
    reply->deleteLater();

    if(!triggers.has_value())
        return;

    triggers_.clear();

    const QJsonArray array = triggers.value();
    for (const auto &ref : array)
    {
        const QJsonObject &trigger = ref.toObject();
        const QString triggerName = trigger.value("triggername").toString();
        if (triggerName.isEmpty())
            continue;

        if (const auto type = Trigger::fromApiString(trigger.value("type").toString());
            type.has_value())
        {
            triggers_.emplace_back(Trigger(trigger));
        }
    }

    // The server should have all or none of the triggers
    if (triggers_.empty())
        createMissingTriggers();
    else
        triggersExistOnServer_ = true;

    emit dataReady();
}

QJsonArray FarmingData::createRequestArray() const
{
    QJsonArray array;

    for (auto &triggerName : triggerSet_)
    {
        QJsonObject obj;
        obj.insert("triggername", triggerName);
        array.push_back(obj);
    }

    return array;
}


void FarmingData::createMissingTriggers()
{
    qDebug() << "Create missing triggers";
    // create local data, user need to update config before it is sent to server.
    // can not guess a default tag to watch
    triggers_.emplace_back(
        Trigger(TriggerType::TriggerTwoValues, "seedheating", "",
            {.rule = TwoValueTrigger::TriggerBelowValue, .value = 20 - temperatureDelta_},
                {.rule = TwoValueTrigger::TriggerAboveValue, .value = 20 + temperatureDelta_}));


    int hours12 = 12 * 60 * 60;
    int target = 7 * 60 * 60;
    triggers_.emplace_back(
        Trigger(TriggerType::TriggerOnTime, "growlighton", "system.time", target, hours12));
}
