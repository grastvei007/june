#include "logvaluedata.h"

#include <optional>

#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>
#include <QNetworkReply>

#include <tagsystem/util/json.h>
#include <tagsystem/util/tagutil.h>

LogValue::LogValue(const QString &tagSocketSubsystem,
                   const QString &tagSocketName,
                   const QString &tagSubsystem,
                   const QString &tagName)
    : tagSocketSubsystem_(tagSocketSubsystem)
    , tagSocketName_(tagSocketName)
    , tagSubsystem_(tagSubsystem)
    , tagName_(tagName)
{
}

QString LogValue::tagSocketFullName() const
{
    return QString("%1.%2)").arg(tagSocketSubsystem_, tagSocketName_);
}

const QString &LogValue::tagSocketSubsystem() const
{
    return tagSocketSubsystem_;
}

const QString &LogValue::tagSocketName() const
{
    return tagSocketName_;
}

QString LogValue::tag() const
{
    return QString("%1.%2").arg(tagSubsystem_, tagName_);
}

LogValueData::LogValueData(QNetworkAccessManager &nam,
                           QNetworkRequestFactory &networkRequestFactory,
                           QObject *parent) :
    networkAccessManager_(nam),
    networkRequestFactory_(networkRequestFactory),
    QObject{parent}
{

}

const LogValue &LogValueData::value(int index) const
{
    return logValues_.at(index);
}

int LogValueData::numberOfValue() const
{
    return logValues_.size();
}

void LogValueData::fetchFromServer()
{
    QNetworkReply *reply = networkAccessManager_.get(
        networkRequestFactory_.createRequest("/logvalue/get"));
    connect(reply, &QNetworkReply::finished, this, &LogValueData::onFetchFromServerFinnished);
}

void LogValueData::deleteLogValue(int index)
{    
    auto logValue = logValues_.at(index);
    QJsonObject obj;
    obj.insert("tagsocket", logValue.tagSocketFullName());
    QJsonDocument document(obj);

    QNetworkReply* reply = networkAccessManager_.post(
        networkRequestFactory_.createRequest("/logvalue/delete"), document.toJson());
    connect(reply, &QNetworkReply::finished, this, &LogValueData::onDeleteFinnished);

    logValues_.erase(logValues_.begin() + index);
}

void LogValueData::onFetchFromServerFinnished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    auto json = util::json::byteArrayToJsonArray(reply->readAll());
    reply->deleteLater();

    if(!json.has_value())
        return;

    logValues_.clear();

    const QJsonArray array = json.value();
    for(const auto &ref : array)
    {
        const QJsonObject& logValue = ref.toObject();

        const QString tagSocketSubsystem = logValue.value("tagsocket").toString();
        const QString tagSocketName = logValue.value("name").toString();
        const QString tagSubsystem = logValue.value("tagsubsystem").toString();
        const QString tagName = logValue.value("tagname").toString();

        logValues_.emplace_back(LogValue(tagSocketSubsystem, tagSocketName, tagSubsystem, tagName));
    }
    emit dataReady();
}

void LogValueData::onDeleteFinnished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
}

void LogValueData::addLogValue(const QString &tagsocketSubsystem,
                               const QString &tagsocketName,
                               const QString &tag)
{

    auto [tagSubsystem, tagName] = util::tag::splitFullName(tag);

    QJsonObject obj;
    obj.insert("tagsocketsubsystem", tagsocketSubsystem);
    obj.insert("tagsocketname", tagsocketName);
    obj.insert("tagsubsystem", tagSubsystem);
    obj.insert("tagname", tagName);

    QJsonDocument document(obj);

    QNetworkReply* reply = networkAccessManager_.post(
        networkRequestFactory_.createRequest("/logvalue/add"), document.toJson());
    connect(reply, &QNetworkReply::finished, this, &LogValueData::onAddFinnished);
}


void LogValueData::onAddFinnished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    auto add = util::json::byteArrayToJsonObject(reply->readAll());
    reply->deleteLater();

    if(!add.has_value())
        return;

    const QJsonObject obj = add.value();

    const auto tagsocketSubsystem = obj.value("tagsocketsubsystem").toString();
    const auto tagsocketName = obj.value("tagsocketname").toString();
    const auto tagSubsystem = obj.value("tagsubsystem").toString();
    const auto tagName = obj.value("tagname").toString();

    logValues_.emplace_back(LogValue(tagsocketSubsystem, tagsocketName, tagSubsystem, tagName));
    emit logValueAdded();
}
