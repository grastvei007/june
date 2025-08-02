#ifndef TAGSOCKETBINDINGTABLEMODEL_H
#define TAGSOCKETBINDINGTABLEMODEL_H

#include <QAbstractTableModel>

class TagSocketBindingData;

class TagSocketBindingTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Colums {eTagSocket, eType, eTag};
    TagSocketBindingTableModel();
    TagSocketBindingTableModel(TagSocketBindingData *data);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    TagSocketBindingData *data_ = nullptr;
};

#endif // TAGSOCKETBINDINGTABLEMODEL_H
