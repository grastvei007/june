#include "tagsocketbindingdata.h"

#include <optional>

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>

#include <tagsystem/util/json.h>

TagSocketBindingData::TagSocketBindingData(QNetworkAccessManager &nam,
                                           QNetworkRequestFactory &networkRequestFactory,
                                           QObject *parent) :
    networkAccessManager_(nam),
    networkRequestFactory_(networkRequestFactory),
    QObject{parent}
{

}

const TagSocketBinding &TagSocketBindingData::binding(int index) const
{
    return tagSocketBindings_.at(index);
}

int TagSocketBindingData::numberOfBindings() const
{
    return tagSocketBindings_.size();
}

void TagSocketBindingData::updateTag(int index, const QString &tag)
{
    auto element = binding(index);
    QJsonObject obj;
    obj.insert("tagsocket", QString("%1.%2").arg(element.tagSocketSubsystem(), element.tagSocketName()));
    obj.insert("tag", tag);

    QJsonDocument document(obj);
    QNetworkReply *reply = networkAccessManager_.post(
        networkRequestFactory_.createRequest("/tagsocket/hookup"), document.toJson());

    connect(reply, &QNetworkReply::finished, this, &TagSocketBindingData::onHookupOnServerFinnished);
}

void TagSocketBindingData::fetchFromServer()
{
    QNetworkReply *reply = networkAccessManager_.get(
        networkRequestFactory_.createRequest("/tagsocket/get"));
    connect(reply, &QNetworkReply::finished, this, &TagSocketBindingData::onFetchFromServerFinnished);
}

void TagSocketBindingData::onFetchFromServerFinnished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    auto tagsocketBinding = util::json::byteArrayToJsonArray(reply->readAll());
    reply->deleteLater();

    if(!tagsocketBinding.has_value())
        return;

    tagSocketBindings_.clear();

    const QJsonArray array = tagsocketBinding.value();
    for(const auto &ref : array)
    {
        const QJsonObject &binding = ref.toObject();

        auto tagSocketSubsystem = binding.value("subsystem").toString();
        auto tagSocketName = binding.value("name").toString();
        auto tag = binding.value("tagname").toString();
        auto type = TagSocket::typeFromString(binding.value("type").toString());

        tagSocketBindings_.emplace_back(TagSocketBinding(tagSocketSubsystem, tagSocketName, tag, type));
    }

    emit dataReady();
}

void TagSocketBindingData::onHookupOnServerFinnished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    auto json = util::json::byteArrayToJsonObject(reply->readAll());
    reply->deleteLater();

    if(!json.has_value())
        return;

    QJsonObject obj = json.value();
    auto tagsocketSubsystem = obj.value("subsystem").toString();
    auto tagsocketName = obj.value("name").toString();
    auto tag = obj.value("tagname").toString();

    auto bindingIter = std::find_if(tagSocketBindings_.begin(), tagSocketBindings_.end(), [&tagsocketSubsystem, &tagsocketName](const auto& elm){
        return tagsocketName == elm.tagSocketName() && tagsocketSubsystem == elm.tagSocketSubsystem();
    });

    bindingIter->setTag(tag);
    emit bindingUpdated(std::distance(tagSocketBindings_.begin(), bindingIter));
}

TagSocketBinding::TagSocketBinding(const QString &tagSocketSubsystem,
                                   const QString &tagSocketName,
                                   const QString &tag,
                                   TagSocket::Type type) :
    tagSocketSubsystem_(tagSocketSubsystem),
    tagSocketName_(tagSocketName),
    tag_(tag),
    type_(type)
{

}

void TagSocketBinding::setTag(const QString &tag)
{
    tag_ = tag;
}
