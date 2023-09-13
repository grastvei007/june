#ifndef TRIGGERDATA_H
#define TRIGGERDATA_H

#include <vector>
#include <any>
#include <optional>

#include <QObject>

#include "trigger.h"


class TriggerData : public QObject
{
    Q_OBJECT
public:
    explicit TriggerData(QObject *parent = nullptr);

    void addTrigger(std::any trigger);

    std::any getTrigger(int index);
    int numberOfTriggers() const;
signals:
    void triggerAdded(int index);

private:
    std::vector<std::any> triggers_;

};

inline auto *trigger_cast(std::any &trigger)
{
    if (Trigger<bool> *t = std::any_cast<Trigger<bool> *>(trigger))
        return t;

    Q_UNREACHABLE();
}

#endif // TRIGGERDATA_H
