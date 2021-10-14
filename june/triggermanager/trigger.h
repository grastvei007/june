#ifndef TRIGGER_H
#define TRIGGER_H

#include <QString>

class Trigger
{
public:
    Trigger(const QString &name);

    const QString& name() const;
    bool isActive() const;

private:
    QString name_;
    bool isActive_ = false;
};

#endif // TRIGGER_H
