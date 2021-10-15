#ifndef VALUETRIGGER_H
#define VALUETRIGGER_H

#include "../trigger.h"

class ValueTrigger : public Trigger
{
public:
    ValueTrigger(QString name, QString tagname, TriggerFunction::Values trigger, double triggerValue);

protected slots:
    void onTagSocketValueChanged(TagSocket *tagSocket) override;

private:
    double triggerValue_;
};

#endif // VALUETRIGGER_H
