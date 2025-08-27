#include "triggerdatatablemodel.h"
#include "data/trigger.h"
#include <QColor>
#include <QString>

TriggerDataTableModel::TriggerDataTableModel(TriggerData *triggerData) :
    triggerData_(triggerData)
{
    connect(triggerData_, &TriggerData::triggerAdded, this, &TriggerDataTableModel::onTriggerAdded);

    connect(triggerData_, &TriggerData::dataReady, this, [this]() {
        beginResetModel();
        endResetModel();
    });
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
            case eTriggerValue:
                return "Trigger value";
            case eActive:
                return "Acvive";
            case eEnabled:
                return "Enabled";
            default:
                break;
            }
        }
    } else if (orientation == Qt::Vertical) {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return QString::number(section);
    }

    return {};
}


QVariant TriggerDataTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        auto trigger = triggerData_->getTrigger(index.row());

        switch (index.column()) {
        case eTriggerName:
            return trigger.triggerName();
        case eTargetTagName:
            return trigger.watchTag();
        case eTriggerValue:
        {
            if(trigger.triggerType() == TriggerType::TriggerEveryTimeAbove || trigger.triggerType() == TriggerType::TriggerEveryTimeBelow)
            {
                return trigger.targetValued();
            }
            else if(trigger.triggerType() == TriggerType::TriggerOnTime)
            {
                return trigger.targetValuei();
            }
            return "";
        }
        case eActive:
            return true;
        case eEnabled:
            return trigger.isEnabled();
        default:
            break;
        }
    } else if (role == Qt::BackgroundRole) {
        if (index.row() == 0)
            return false;
        else if ((index.row() % 2) == 1)
            return QColor(Qt::gray);
    }

    return {};
}

bool TriggerDataTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index);
    Q_UNUSED(value);
    Q_UNUSED(role);
    return false;
}

Qt::ItemFlags TriggerDataTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled;
}

bool TriggerDataTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(row);
    Q_UNUSED(count);
    Q_UNUSED(parent);

    /*auto trigger = new Trigger<bool>("Test", nullptr);
    trigger->setValue(false);
    triggerData_->addTrigger(trigger);*/

    return true;
}

void TriggerDataTableModel::onTriggerAdded(int)
{
    beginResetModel();
    QModelIndex top = index(0, eTriggerName);
    QModelIndex bottom = index(rowCount(), eActive);
    emit dataChanged(top, bottom);
    endResetModel();
}
