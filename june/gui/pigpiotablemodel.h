#ifndef PIGPIOTABLEMODEL_H
#define PIGPIOTABLEMODEL_H

#include <QAbstractTableModel>

#include "data/pigpiodata.h"

class PiGpioTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
	enum Colums {eWiringPiPin, eTag, eDirection, eHookupTag, eEnabled};
    PiGpioTableModel();
    PiGpioTableModel(PiGpioData *data);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    PiGpioData *data_;
};

#endif // PIGPIOTABLEMODEL_H
