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

#endif // TRIGGER_H
