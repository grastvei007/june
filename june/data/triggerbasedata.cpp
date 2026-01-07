#include "triggerbasedata.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>
#include <tagsystem/util/json.h>

TriggerBaseData::TriggerBaseData(QNetworkAccessManager &nam,
								 QNetworkRequestFactory &networkRequestFactory,
								 QObject *parent)
	: networkRequestFactory_(networkRequestFactory)
	, networkAccessManager_(nam)
	, QObject{parent}
{}

QJsonArray TriggerBaseData::createRequestArray(const std::vector<QString> &list) const
{
	QJsonArray array;

	for (auto &triggerName : list)
	{
		QJsonObject obj;
		obj.insert("triggername", triggerName);
		array.push_back(obj);
	}

	return array;
}

void TriggerBaseData::fetchFromServer()
{
	QJsonDocument doc(createRequestArray(requestedTriggers_));

	QNetworkReply *reply = networkAccessManager_.post(networkRequestFactory_.createRequest(
														  "/trigger/get"),
													  doc.toJson());
	connect(reply, &QNetworkReply::finished, this, &TriggerBaseData::onFetchFromServerFinnished);
}

void TriggerBaseData::sendToServer()
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
	}
	else
	{
		QNetworkReply *reply = networkAccessManager_.post(networkRequestFactory_.createRequest(
															  "/trigger/create"),
														  doc.toJson());
		triggersExistOnServer_ = true;
	}
}

int TriggerBaseData::numberOfTriggers() const
{
	return triggers_.size();
}

const Trigger &TriggerBaseData::getTrigger(unsigned int index) const
{
	return triggers_.at(index);
}

Trigger &TriggerBaseData::getTrigger(unsigned int index)
{
	return triggers_.at(index);
}

void TriggerBaseData::onFetchFromServerFinnished()
{
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	auto triggers = util::json::byteArrayToJsonArray(reply->readAll());
	reply->deleteLater();

	if (!triggers.has_value())
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
