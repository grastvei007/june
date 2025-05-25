#ifndef TRIGGERDATA_H
#define TRIGGERDATA_H

#include <vector>
#include <optional>

#include <QObject>
#include <QNetworkRequestFactory>
#include <QNetworkAccessManager>

#include "trigger.h"


class TriggerData : public QObject
{
    Q_OBJECT
public:
    explicit TriggerData(QNetworkAccessManager &nam, QNetworkRequestFactory &networkRequestFactory, QObject *parent = nullptr);

    void addTrigger(const Trigger &trigger);

    const Trigger& getTrigger(unsigned int index) const;
    int numberOfTriggers() const;
signals:
    void triggerAdded(int index);

private:
    std::vector<Trigger> triggers_;
    QNetworkRequestFactory& networkRequestFactory_;
    QNetworkAccessManager& networkAccessManager_;
};


#endif // TRIGGERDATA_H
