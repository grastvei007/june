#ifndef TRIGGERTABLEMODEL_H
#define TRIGGERTABLEMODEL_H

#include <QAbstractTableModel>

class TriggerData;

class TriggerTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TriggerTableModel(TriggerData *aData);

signals:

private:
    TriggerData *mData;
};

#endif // TRIGGERTABLEMODEL_H
