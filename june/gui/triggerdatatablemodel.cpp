#include "triggerdatatablemodel.h"
#include <QColor>

#include "data/trigger.h"

TriggerDataTableModel::TriggerDataTableModel(TriggerData *triggerData) :
    triggerData_(triggerData)
{

}

int TriggerDataTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return triggerData_->numberOfTriggers();
}

int TriggerDataTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant TriggerDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            switch (section) {
            case eTriggerName:
                return "Trigger name";
            case eTargetTagName:
                return "Target Tag";
            case eValue:
                return "Value";
            case eTriggerValue:
                return "Trigger value";
            case eActive:
                return "Acvive";
            default:
                break;
            }
        }
    } else if (orientation == Qt::Vertical) {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return QString::number(section);
    }

    return QVariant();
}


QVariant TriggerDataTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        auto triggerData = triggerData_->getTrigger(index.row()).value();
        if (triggerData.type() == typeid(Trigger<bool>)) {
            auto &trigger = std::any_cast<Trigger<bool> &>(triggerData);

            switch (index.column()) {
            case eTriggerName:
                return trigger.name();
            case eTargetTagName:
                return "";
                 //trigger.tagName();
            case eValue:
                return QString();
            case eTriggerValue:
                return trigger.targetValue();
            case eActive:
                return trigger.isActive();
            default:
                break;
            }
        }
    } else if (role == Qt::BackgroundRole) {
        if (index.row() == 0)
            return false;
        else if ((index.row() % 2) == 1)
            return QColor(Qt::gray);
    }

    return QVariant();
}

bool TriggerDataTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

Qt::ItemFlags TriggerDataTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled;
}

bool TriggerDataTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    return false;
}
