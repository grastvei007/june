#ifndef CENTRALWIDGETFACTORY_H
#define CENTRALWIDGETFACTORY_H

#include <QWidget>
#include <QDebug>
#include <map>
#include <type_traits>

#include "../data/triggerdata.h"

template<typename Type, typename DataType>
QWidget* createType(QObject *dataClass)
{
    return new Type(static_cast<DataType*>(dataClass), nullptr);
}

class CentralWiddgetFactory
{
public:
    CentralWiddgetFactory() = default;

    QWidget* createWidget(const QString &key)
    {
        if(constructors_.find(key) == constructors_.end())
            return nullptr;

        Creator create = constructors_[key];
        return create(dataClasses_[key]);
    }


    template<typename Type, typename DataType>
    void add(const QString &key, QObject *dataClass);

protected:
    typedef QWidget* (*Creator)(QObject *);

    std::map<QString, Creator> constructors_;
    std::map<QString, QObject*> dataClasses_;
};

template<typename Type, typename DataType>
void CentralWiddgetFactory::add(const QString &key, QObject *dataClass)
{
    if(typeid(DataType) == typeid(*dataClass))
    {
        Creator creator = &createType<Type, DataType>;
        constructors_.emplace(key, creator);
        dataClasses_.emplace(key, dataClass);
    }
    else
    {
        qWarning() << "CentralWiddgetFactory: Invalid data class for widget.";
    }
}

#endif // CENTRALWIDGETFACTORY_H
