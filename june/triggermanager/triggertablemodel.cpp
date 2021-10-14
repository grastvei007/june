#include "triggertablemodel.h"

#include <QColor>

TriggerTableModel::TriggerTableModel(TriggerManager *triggerManager, QObject *parent) :
    QAbstractTableModel(parent),
    triggerManager_(triggerManager)
{

}

int TriggerTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return triggerManager_->numberOfTriggers();
}

int TriggerTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant TriggerTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        auto trigger = triggerManager_->getTriggerByIndex(index.row());
        if(!trigger)
            return QVariant(QVariant::Invalid);
        switch (index.column())
        {
            case eTriggerName:
                return trigger->name();
            case eActive:
                return trigger->isActive();
            default:
                break;
        }


    }
    else if(role == Qt::BackgroundRole)
    {
        if(index.row() == 0)
            return false;
        else if((index.row() % 2) == 1)
            return QColor(Qt::gray);
    }
    return QVariant(QVariant::Invalid);
}

QVariant TriggerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole || role == Qt::EditRole)
        {
            switch (section)
            {
            case eTriggerName:
                return "Trigger Name";
            case eActive:
                return "Active";
            default:
                return "Unknown";

            }
        }
    }
    else if(orientation == Qt::Vertical)
    {
        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return QString::number(section);
    }
    return QVariant(QVariant::Invalid);
}


Qt::ItemFlags TriggerTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled;
}

QStringList TriggerTableModel::triggerTypes()
{
    return {"TriggerValue"};
}

QStringList TriggerTableModel::trigger()
{
    return {"Trigger above value", "Trigger below value"};
}
