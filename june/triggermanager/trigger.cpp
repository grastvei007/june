#include "trigger.h"

#include <QDebug>

Trigger::Trigger(const QString &name) : name_(name)
{

}

const QString &Trigger::name() const
{
    return name_;
}

bool Trigger::isActive() const
{
    return isActive_;
}

TriggerType Trigger::triggerTypeFromString(QString type)
{
    if(type == "TriggerValue")
        return TriggerType::eTriggerValue;

    return TriggerType::eNone;
}

void Trigger::onTagSocketValueChanged(TagSocket *tagSocket)
{
    Q_UNUSED(tagSocket);
    qDebug() << __FUNCTION__ << "Override this";
}

void Trigger::setTag(Tag *tag)
{
    tag_ = tag;
    if(tagSocket_)
        tagSocket_->hookupTag(tag_);
}

void Trigger::setTagSocket(TagSocket *tagSocket)
{
    tagSocket_ = tagSocket;
    if(tag_)
        tagSocket_->hookupTag(tag_);

    connect(tagSocket_, qOverload<TagSocket*>(&TagSocket::valueChanged), this, &Trigger::onTagSocketValueChanged);
}
