#ifndef GARDENADATATABLEMODEL_H
#define GARDENADATATABLEMODEL_H

#include <QAbstractTableModel>

#include "data/gardenadata.h"

class GardenaDataTableModel : public QAbstractTableModel
{
	Q_OBJECT
  public:
	enum Columns { eName, eStart, eStop, eEnable };
	GardenaDataTableModel();
	GardenaDataTableModel(GardenaData *gardenaData);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section,
						Qt::Orientation orientation,
						int role = Qt::DisplayRole) const override;

	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;

  private:
	GardenaData *data_ = nullptr;
};

#endif // GARDENADATATABLEMODEL_H
