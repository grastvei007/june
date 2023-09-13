#ifndef TRIGGER_H
#define TRIGGER_H

#include <memory>

#include <QString>
#include <QObject>
#include <QTimer>

#include <tagsystem/tag.h>
#include <tagsystem/tagsocket.h>

template<typename T>
class Trigger : public QObject
{
//    Q_OBJECT
public:
    Trigger(const QString &triggerName, Tag *targetTag);

    void setValue(T t){ setValue_ = t;}
    void triggerOnTimout(int minuts);

    void activate();
    void deactivate();
    void setActive(bool isActive);
    T targetValue() const{ return setValue_;}

    bool isActive() const { return isAvtive_; }
    QString name() const { return triggerName_; }
    QString tagName() const;

signals:
    void activated();
    void deactivated();
    void triggered();

private slots:
    void onTimout();

private:
    QString triggerName_;
    bool isAvtive_ = false;

    std::unique_ptr<QTimer> timer_;

    T setValue_;
    Tag *targetTag_ = nullptr;

    TagSocket* triggerTagSocket_ = nullptr;
};

template<typename T>
Trigger<T>::Trigger(const QString &triggerName, Tag *targetTag)
    : triggerName_(triggerName)
    , targetTag_(targetTag)
{
    triggerTagSocket_ = TagSocket::createTagSocket<T>("trigger", triggerName);
    triggerTagSocket_->writeValue(setValue_);

    if(targetTag_)
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

#endif // TRIGGER_H
