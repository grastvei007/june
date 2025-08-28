#include "farmingdata.h"

FarmingData::FarmingData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent) :
    networkRequestFactory_(networkRequestFactory),
    networkAccessManager_(nam),
    QObject(parent)
{

}
