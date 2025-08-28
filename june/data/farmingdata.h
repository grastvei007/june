#ifndef FARMINGDATA_H
#define FARMINGDATA_H

#include <QObject>
#include <QNetworkRequestFactory>
#include <QNetworkAccessManager>

class FarmingData : public QObject
{
    Q_OBJECT
public:
    FarmingData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent = nullptr);

private:
    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;
};

#endif // FARMINGDATA_H
