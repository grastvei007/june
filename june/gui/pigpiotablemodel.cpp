#include "pigpiotablemodel.h"

#include <QColor>

PiGpioTableModel::PiGpioTableModel() {}

PiGpioTableModel::PiGpioTableModel(PiGpioData *data)
    : data_(data)
{
    connect(data_, &PiGpioData::directionUpdated, this, [this]() {
        QModelIndex top = index(0, eDirection);
        QModelIndex bottom = index(data_->numberOfPins()-1, eDirection);
        emit dataChanged(top, bottom);
    });

    connect(data_, &PiGpioData::enabledUpdated, this, [this]() {
        QModelIndex top = index(0, eEnabled);
        QModelIndex bottom = index(data_->numberOfPins()-1, eEnabled);
        emit dataChanged(top, bottom);
    });
}

int PiGpioTableModel::rowCount(const QModelIndex &parent) const
{
    return data_->numberOfPins();
}

int PiGpioTableModel::columnCount(const QModelIndex &parent) const
{
	return 5;
}

QVariant PiGpioTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        const auto &gpioPin = data_->getGpioPin(index.row());

        switch (index.column())
        {
        case eWiringPiPin:
            return gpioPin.wiringPiPin();
		case eHookupTag:
			return gpioPin.hookupTag();
        case eTag:
            return gpioPin.tagFullName();
        case eDirection:
            return gpioPin.direction();
        case eEnabled:
            return gpioPin.enabled() ? "enabled" : "disabled";

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

QVariant PiGpioTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            switch (section)
            {
            case eWiringPiPin:
                return "Wiring pi pin";
            case eTag:
                return "Tag";
            case eDirection:
                return "Direction";
			case eHookupTag:
				return "Hookup to Tag";
            case eEnabled:
                return "Enabled";
            default:
                break;
            }
        }

    } else if (orientation == Qt::Vertical)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return QString::number(section);
    }

    return QVariant();
}

bool PiGpioTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (index.column() == eDirection)
        {
            data_->updatePinDirection(index.row(), value.toString());
            return true;
        } else if (index.column() == eEnabled)
        {
            data_->updatePinEnable(index.row(), value.toBool());
            return true;
        }
    }

    return false;
}

Qt::ItemFlags PiGpioTableModel::flags(const QModelIndex &index) const
{
    if(index.column() == eDirection || index.column() == eEnabled)
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled;
}
