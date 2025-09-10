#ifndef FARMINGDATA_H
#define FARMINGDATA_H

#include <vector>

#include <QObject>
#include <QNetworkRequestFactory>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QDateTime>
#include <QStringList>

#include "triggerdata.h"


class FarmingData : public QObject
{
    Q_OBJECT
public:
    FarmingData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent = nullptr);

    void fetchFromServer();

    double seedHeatingOn() const;
    double seedHeatingOff() const;
    QString seedWatchTag() const;
    QString seedTemperatureSensor() const;
    bool isSeedHeatingEnabled() const;

    QTime turnOnGrowLight() const;
    QTime turnOffGrowLight() const;
    bool isTurnOffGrowLightEnabled() const;

    QStringList availableTemperatureSensors() const;

    void setTemperatureSensor(const QString &sensor);
    void setTempeperature(double temperature);
    void enableSeedControl(bool enable);
    void enableGrowLight(bool enable);
    void setGrowLigtTime(int startTime, int duration);

    void sendToServer();

signals:
    void dataReady();

private slots:
    void onFetchFromServerFinnished();

private:
    QJsonArray createRequestArray() const;
    void createMissingTriggers();

    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;

    const double temperatureDelta_ = 0.5;

    std::vector<QString> triggerSet_;
    std::vector<Trigger> triggers_;
    bool triggersExistOnServer_ = false;
};

#endif // FARMINGDATA_H
