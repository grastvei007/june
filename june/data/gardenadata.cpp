#include "gardenadata.h"

GardenaData::GardenaData(QNetworkAccessManager &nam,
						 QNetworkRequestFactory &networkRequestFactory,
						 QObject *parent)
	: networkRequestFactory_(networkRequestFactory)
	, networkAccessManager_(nam)
	, QObject(parent)
{}
