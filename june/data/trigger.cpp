#include "trigger.h"

template<typename T>
Trigger<T>::Trigger(const QString &triggerName, Tag *targetTag)
    : triggerName_(triggerName)
    , targetTag_(targetTag)
{
    triggerTagSocket_ = TagSocket::createTagSocket("trigger", triggerName, T::type());
    triggerTagSocket_->hookupTag(targetTag_);
}

template<typename T>
void Trigger<T>::triggerOnTimout(int minuts)
{
    timer_ = std::make_unique<QTimer>();
    timer_->setInterval(minuts * 60 * 1000);
}

template<typename T>
void Trigger<T>::activate()
{
    isAvtive_ = true;
    emit activate();
    if (timer_) {
        connect(timer_.get(), &QTimer::timeout, this, &Trigger::onTimout);
        timer_->start();
    }
}

template<typename T>
void Trigger<T>::deactivate()
{
    isAvtive_ = false;
    emit deactivate();
}

template<typename T>
void Trigger<T>::setActive(bool isActive)
{
    isAvtive_ = isActive;
    if (isAvtive_)
        emit activate();
    else
        emit deactivated();
}

template<typename T>
QString Trigger<T>::tagName() const
{
    if (!targetTag_)
        return QString();

    return targetTag_->getFullName();
}

template<typename T>
void Trigger<T>::onTimout()
{
    triggerTagSocket_->writeValue(setValue_);
    emit triggered();
}
