#include "valuetrigger.h"

#include <QDebug>

#include <tagsystem/taglist.h>
#include <tagsystem/tag.h>

ValueTrigger::ValueTrigger(QString name, QString tagname, TriggerFunction::Values trigger, double triggerValue) :
    Trigger(name),
    triggerValue_(triggerValue)
{

    Tag *tag = TagList::sGetInstance().findByTagName(tagname);
    TagSocket *tagSocket = nullptr;
    if(tag->getType() == Tag::eDouble)
        tagSocket = TagSocket::createTagSocket("Trigger", name, TagSocket::eDouble);
    else if(tag->getType() == Tag::eInt)
        tagSocket = TagSocket::createTagSocket("Trigger", name, TagSocket::eInt);
    else
        qDebug() << __FUNCTION__ << "Invalid tag type";


    setTag(tag);
    setTagSocket(tagSocket);
}

void ValueTrigger::onTagSocketValueChanged(TagSocket *tagSocket)
{
    if(!isActive())
        return;

    double val;
    if(tagSocket->getType() == TagSocket::eDouble)
    {
        if(!tagSocket->readValue(val))
            return;
    }
    else if(tagSocket->getType() == TagSocket::eInt)
    {
        int temp;
        if(!tagSocket->readValue(temp))
            return;
        val = temp;
    }
    else
        return;



}
