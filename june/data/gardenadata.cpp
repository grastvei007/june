#include "gardenadata.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QString>
#include "triggerdata.h"
#include <ranges>
#include <tagsystem/util/json.h>
#include <vector>

GardenaData::GardenaData(QNetworkAccessManager &nam,
						 QNetworkRequestFactory &networkRequestFactory,
						 QObject *parent)
	: TriggerBaseData(nam, networkRequestFactory, parent)
{
	requestedTriggers_.emplace_back("water_relay_1");
	requestedTriggers_.emplace_back("water_relay_2");
	requestedTriggers_.emplace_back("water_relay_3");
}

void GardenaData::createMissingTriggers()
{
	// triggers do not exist on server create them, and disable them by default.

	int duration = 1 * 60 * 60 * 1000; // one hour
	int target = 7 * 60 * 60 * 1000;   // 7 am

	triggers_.emplace_back(
		Trigger(TriggerType::TriggerOnTime, "water_relay_1", "system.time", target, duration));
	triggers_.back().setEnable(false);
	triggers_.emplace_back(
		Trigger(TriggerType::TriggerOnTime, "water_relay_2", "system.time", target, duration));
	triggers_.back().setEnable(false);
	triggers_.emplace_back(
		Trigger(TriggerType::TriggerOnTime, "water_relay_3", "system.time", target, duration));
	triggers_.back().setEnable(false);
}

