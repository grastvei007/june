#include "pigpiodata.h"

#include <QNetworkRequestFactory>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>

#include <optional>
#include <ranges>

#include <tagsystem/util/json.h>


RpiGpioPin::RpiGpioPin(const QString &tagSubsystem,
                       const QString &tagName,
                       int wiringPiPin,
                       const QString &direction,
                       bool enabled)
    : tagSubsystem_(tagSubsystem)
    , tagName_(tagName)
    , wiringPiPin_(wiringPiPin)
    , direction_(direction)
    , enabled_(enabled)
{}

QString RpiGpioPin::tagFullName() const
{
    return QString("%1.%2").arg(tagSubsystem_, tagName_);
}

const QString &RpiGpioPin::direction() const
{
    return direction_;
}

int RpiGpioPin::wiringPiPin() const
{
    return wiringPiPin_;
}

bool RpiGpioPin::enabled() const
{
    return enabled_;
}

void RpiGpioPin::setDirection(const QString &direction)
{
    direction_ = direction;
}

void RpiGpioPin::setEnabled(bool enabled)
{
    enabled_ = enabled;
}

PiGpioData::PiGpioData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent)
    : QObject(parent)
    , networkRequestFactory_(networkRequestFactory)
    , networkAccessManager_(nam)
{

}

void PiGpioData::fetchFromServer()
{
    QNetworkReply *reply = networkAccessManager_.get(
        networkRequestFactory_.createRequest("/gpio/get"));
    connect(reply, &QNetworkReply::finished, this, &PiGpioData::onFetchFromServerFinnished);
}

int PiGpioData::numberOfPins() const
{
    return gpioPins_.size();
}

const RpiGpioPin &PiGpioData::getGpioPin(int index) const
{
    return gpioPins_.at(index);
}

void PiGpioData::updatePinDirection(int index, QString direction)
{
    const auto &pin = getGpioPin(index);
    QJsonObject obj;
    obj.insert("wiringpi", pin.wiringPiPin());
    obj.insert("dir", direction);
    updateConfig(obj);
}

void PiGpioData::updatePinEnable(int index, bool enabled)
{
    const auto &pin = getGpioPin(index);
    QJsonObject obj;
    obj.insert("wiringpi", pin.wiringPiPin());
    obj.insert("enabled", enabled);
    updateConfig(obj);
}

void PiGpioData::onFetchFromServerFinnished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    auto gpioPins = util::json::byteArrayToJsonArray(reply->readAll());
    reply->deleteLater();

    if (!gpioPins.has_value())
        return;

    gpioPins_.clear();

    const QJsonArray array = gpioPins.value();
    for (const auto &ref : array)
    {
        const QJsonObject &pin = ref.toObject();

        auto subsystem = pin.value("subsystem").toString();
        auto tagName = pin.value("tag").toString();
        auto wiringPiPin = pin.value("wiringpi").toInt();
        auto dir = pin.value("dir").toString();
        auto enabled = pin.value("enabled").toBool();

        gpioPins_.emplace_back(subsystem, tagName, wiringPiPin, dir, enabled);
    }

    emit dataReady();
}

void PiGpioData::updateConfig(const QJsonObject &obj)
{
    QNetworkReply *reply = networkAccessManager_.post(networkRequestFactory_.createRequest(
                                                          "/gpio/update"),
                                                      QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, &PiGpioData::onUpdateResponseFromServer);
}

void PiGpioData::onUpdateResponseFromServer()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    auto gpioPin = util::json::byteArrayToJsonObject(reply->readAll());
    reply->deleteLater();

    if (!gpioPin.has_value())
        return;

    const QJsonObject value = gpioPin.value();

    auto wiringPiPin = value.value("wiringpi").toInt();
    for (auto &pin : gpioPins_ | std::views::filter([&wiringPiPin](auto &pin) {
                         return pin.wiringPiPin() == wiringPiPin;
                     }))
    {
        if (value.contains("dir"))
        {
            pin.setDirection(value.value("dir").toString());
            emit directionUpdated();
        }
        if (value.contains("enabled"))
        {
            pin.setEnabled(value.value("enabled").toBool());
            emit enabledUpdated();
        }
    }
}
