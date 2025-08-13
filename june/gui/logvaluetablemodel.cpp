#include "logvaluetablemodel.h"

#include <QColor>

LogValueTableModel::LogValueTableModel() {}

LogValueTableModel::LogValueTableModel(LogValueData *data) :
    data_(data)
{
    connect(data_, &LogValueData::dataReady, this, [this](){
        beginResetModel();
        endResetModel();
    });

    connect(data_, &LogValueData::logValueAdded, this, [this](){
        beginResetModel();
        insertRow(data_->numberOfValue());
        endResetModel();
    });
}

int LogValueTableModel::rowCount(const QModelIndex &parent) const
{
    return data_->numberOfValue();
}

int LogValueTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant LogValueTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        const auto& logValue = data_->value(index.row());
        switch(index.column())
        {
        case eTagSockeSubsystem:
            return logValue.tagSocketSubsystem();
        case eTagSocketName:
            return logValue.tagSocketName();
        case eTag:
            return logValue.tag();
        }
    } else if (role == Qt::BackgroundRole) {
        if (index.row() == 0)
            return false;
        else if ((index.row() % 2) == 1)
          return QColor(Qt::gray);
    }

    return {};
}

QVariant LogValueTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            switch (section)
            {
            case eTagSockeSubsystem:
                return "TagSocket Subsystem (influsDb table)";
            case eTagSocketName:
                return "TagSocket Name (influxDb value name)";
            case eTag:
                return "Tag: value to be logged";
            default:
                break;
            }
        }

    } else if (orientation == Qt::Vertical)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return QString::number(section);
    }

    return {};
}

bool LogValueTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    return false;
}

Qt::ItemFlags LogValueTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled;
}

bool LogValueTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count);
    data_->deleteLogValue(row);
    endRemoveColumns();

    return true;
}
