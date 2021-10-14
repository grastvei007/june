#ifndef TRIGGERTABLEMODEL_H
#define TRIGGERTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

#include "triggermanager.h"


class TriggerTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns
    {
        eTriggerName,
        eActive
    };

    TriggerTableModel(TriggerManager *triggerManager, QObject *aParent = nullptr);


    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QStringList triggerTypes();
    QStringList trigger();

private:
    TriggerManager *triggerManager_ = nullptr;
};

#endif // TRIGGERTABLEMODEL_H
