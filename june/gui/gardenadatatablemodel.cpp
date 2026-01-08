#include "gardenadatatablemodel.h"
#include <QColor>
#include <QDateTime>

GardenaDataTableModel::GardenaDataTableModel() {}

GardenaDataTableModel::GardenaDataTableModel(GardenaData *gardenaData)
	: data_(gardenaData)
{
	connect(data_, &GardenaData::dataReady, this, [this]() {
		beginResetModel();
		endResetModel();
	});
}

int GardenaDataTableModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return data_->numberOfTriggers();
}

int GardenaDataTableModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 4;
}

QVariant GardenaDataTableModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		auto trigger = data_->getTrigger(index.row());

		switch (index.column())
		{
			case eName:
				return trigger.triggerName();
			case eStart:
				{
					auto start = trigger.targetValuei();
					return QTime::fromMSecsSinceStartOfDay(start).toString();
				}
			case eStop:
				{
					auto start = trigger.targetValuei();
					auto duration = trigger.duration();
					return QTime::fromMSecsSinceStartOfDay(start + duration).toString();
				}
			case eEnable:
				return trigger.isEnabled();
			default:
				break;
		}
	}
	else if (role == Qt::BackgroundRole)
	{
		if (index.row() == 0)
			return false;
		else if ((index.row() % 2) == 1)
			return QColor(Qt::gray);
	}

	return {};
}

QVariant GardenaDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole || role == Qt::EditRole)
		{
			switch (section)
			{
				case eName:
					return "Name";
				case eStart:
					return "Start Time";
				case eStop:
					return "Stop Time";
				case eEnable:
					return "Enabled";
				default:
					break;
			}
		}
	}
	else if (orientation == Qt::Vertical)
	{
		if (role == Qt::DisplayRole || role == Qt::EditRole)
			return QString::number(section);
	}

	return {};
}

bool GardenaDataTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role == Qt::EditRole)
	{
		if (index.column() == eStart)
		{
			if (!value.canConvert(QMetaType::QTime) && value.toString().size() < 2)
				return false;
			auto &trigger = data_->getTrigger(index.row());
			QTime time = value.toTime();
			trigger.setTargetValue(time.msecsSinceStartOfDay());
			return true;
		}
		else if (index.column() == eStop)
		{
			if (!value.canConvert(QMetaType::QTime) && value.toString().size() < 2)
				return false;
			QTime time = value.toTime();

			auto &trigger = data_->getTrigger(index.row());
			int start = trigger.targetValuei();
			int duration = time.msecsSinceStartOfDay() - start;
			trigger.setDuration(duration);
			return true;
		}
		else if (index.column() == eEnable)
		{
			auto &trigger = data_->getTrigger(index.row());
			trigger.setEnable(value.toBool());
			return true;
		}
	}

	return false;
}

Qt::ItemFlags GardenaDataTableModel::flags(const QModelIndex &index) const
{
	Q_UNUSED(index);
	if (index.column() == eStart || index.column() == eStop || index.column() == eEnable)
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;

	return Qt::ItemIsEnabled;
}
