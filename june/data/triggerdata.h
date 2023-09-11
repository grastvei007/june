#ifndef TRIGGERDATA_H
#define TRIGGERDATA_H

#include <vector>
#include <any>
#include <optional>

#include <QObject>


class TriggerData : public QObject
{
    Q_OBJECT
public:
    explicit TriggerData(QObject *parent = nullptr);

    void addTrigger(std::any trigger);

    std::optional<std::any> getTrigger(int index);
    int numberOfTriggers() const;

signals:
    void triggerAdded(int index);

private:
    std::vector<std::any> triggers_;

};

#endif // TRIGGERDATA_H
