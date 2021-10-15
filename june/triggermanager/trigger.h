#ifndef TRIGGER_H
#define TRIGGER_H

#include <QString>
#include <QObject>

#include <tagsystem/tagsocket.h>
#include <tagsystem/tag.h>

enum class TriggerType
{
    eNone,
    eTriggerValue
};



namespace TriggerFunction
{
    enum Values
    {
        eNone,
        eTriggerAboveValue,
        eTriggerBelowValue,
    };

    static Values fromString(QString trigger)
    {
        if(trigger == "None")
            return eNone;
        else if(trigger == "Trigger Above Value")
            return eTriggerAboveValue;
        else if(trigger == "Trigger Below Value")
            return eTriggerBelowValue;

        return eNone;
    }

    static QString toString(Values trigger)
    {
        switch(trigger)
        {
            case eNone:
                return "None";
            case eTriggerAboveValue:
                return "Trigger Above Value";
            case eTriggerBelowValue:
                return "Trigger Below Value";
            default:
                return "Unknown";
        }
    }
}


class Trigger : public QObject
{
    Q_OBJECT
public:
    Trigger(const QString &name);

    const QString& name() const;
    bool isActive() const;

    static TriggerType triggerTypeFromString(QString type);

protected slots:
    virtual void onTagSocketValueChanged(TagSocket *tagSocket);

protected:
    void setTag(Tag *tag);
    void setTagSocket(TagSocket *tagSocket);
private:
    TriggerType triggerType_ = TriggerType::eNone;
    QString name_;
    bool isActive_ = false;

    TagSocket *tagSocket_ = nullptr;
    Tag *tag_ = nullptr;
};

#endif // TRIGGER_H
