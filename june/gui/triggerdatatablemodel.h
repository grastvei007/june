#ifndef TRIGGERDATATABLEMODEL_H
#define TRIGGERDATATABLEMODEL_H

#include <QAbstractTableModel>

#include "data/triggerdata.h"

class TriggerDataTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns { eTriggerName, eTargetTagName, eValue, eTriggerValue, eActive };

    TriggerDataTableModel(){};
    TriggerDataTableModel(TriggerData *triggerData);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private slots:
    void onTriggerAdded(int index);

private:
    TriggerData *triggerData_;
};

#endif // TRIGGERDATATABLEMODEL_H
