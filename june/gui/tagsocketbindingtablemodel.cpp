#include "tagsocketbindingtablemodel.h"

#include <QColor>

#include <tagsystem/tagsocket.h>
#include "data/tagsocketbindingdata.h"

TagSocketBindingTableModel::TagSocketBindingTableModel() {}

TagSocketBindingTableModel::TagSocketBindingTableModel(TagSocketBindingData *data) :
    data_(data)
{
    connect(data_, &TagSocketBindingData::dataReady, this, [this](){
        beginResetModel();
        endResetModel();
    });

    connect(data_, &TagSocketBindingData::bindingUpdated, this, [this](int i){
        QModelIndex idx = index(i, eTag);
        emit dataChanged(idx, idx);
    });
}

int TagSocketBindingTableModel::rowCount(const QModelIndex &parent) const
{
    return data_->numberOfBindings();
}

int TagSocketBindingTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant TagSocketBindingTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        const auto &binding = data_->binding(index.row());
        switch (index.column())
        {
        case eTagSocket:
            return QString("%1.%2").arg(binding.tagSocketSubsystem(), binding.tagSocketName());
        case eType:
            return TagSocket::toString(binding.type());
        case eTag:
            return binding.tag();

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

QVariant TagSocketBindingTableModel::headerData(int section,
                                                Qt::Orientation orientation,
                                                int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            switch (section)
            {
            case eTagSocket:
                return "TagSocket";
            case eType:
                return "Type";
            case eTag:
                return "Tag";
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

bool TagSocketBindingTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    data_->updateTag(index.row(), value.toString());
    // normally return true here, but return false instead and the update
    // is done when the reply is returned by server.
    return false;
}

Qt::ItemFlags TagSocketBindingTableModel::flags(const QModelIndex &index) const
{
    if(index.column() == eTag)
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled;
}
