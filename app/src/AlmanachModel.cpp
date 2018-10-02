//#include "prediction-qt/Predictor.h"
#include "prediction-qt/Almanach.h"

#include "AlmanachModel.h"

namespace
{
	template<typename Key, typename Value>
	Value getMapValue(const std::map<Key, Value> &map, const Key &key, const Value &defaultValue = Value())
	{
		const auto it = map.find(key);
		return (it == map.cend()) ? defaultValue : it->second;
	}
}

AlmanachModel::AlmanachModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

AlmanachModel::~AlmanachModel() = default;

int AlmanachModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return almanachs_.size();
}

int AlmanachModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return ColumnCount;
}

QVariant AlmanachModel::data(const QModelIndex &index, int role) const
{
	QVariant result;

	if (index.isValid()) {
		switch (role) {
			case Qt::DisplayRole:
				result = almanachDisplayData(index);
				break;
				
			case Qt::TextAlignmentRole:
				result = QVariant(Qt::AlignLeft | Qt::AlignVCenter);
				break;

			default:
				break;
		}
	}

	return result;
}

QVariant AlmanachModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	// TODO: UlturgashevVV - Попробовать UnorderedMap.
	static const std::map<int, QString> headers = {
		{Number, tr("Number")},
		{Health, tr("Health")},
		{Date, tr("Date")},
		{LiterNumber, tr("Frequency")},
		{Longitude, tr("Longitude")},
		{Eccentricity, tr("Eccentricity")},
		{InclinationCorrection, tr("Inclination correction")},
		{ArgumentPerigee, tr("Argument perigee")},
		{AscendingNodeTime, tr("Ascending node time")},
		{CirculationPeriod, tr("Circulation period")},
		{CirculationVelocity, tr("Circulation velocity")}
	};

	QVariant result;

	if (orientation == Qt::Horizontal) {
		switch (role) {
			case Qt::DisplayRole:
				result = getMapValue(headers, section);
				break;

			case Qt::TextAlignmentRole:
				result = Qt::AlignLeft;
				break;

			default:
				break;
		}
	}

	return result;
}

void AlmanachModel::setAlmanach(const Core::Almanachs &almanachs)
{
	beginResetModel();
	almanachs_ = almanachs;
	endResetModel();
}

Core::Almanachs AlmanachModel::almanachs() const
{
	return almanachs_;
}

QVariant AlmanachModel::almanachDisplayData(const QModelIndex& index) const
{
	QVariant result;
	
	const Core::Almanach almanach = getMapValue(almanachs_, index.row() + 1);
	
	switch (index.column()) {
		case Number:
			result = almanach.number();
			break;
			
		case Health:
			result = almanach.health();
			break;
			
		// TODO: Дописать
		case Date:
			result = 0;
			break;
			
		case LiterNumber:
			result = almanach.literNumber();
			break;
			
		case Longitude:
			result = almanach.longitude();
			break;
			
		case Eccentricity:
			result = almanach.eccentricity();
			break;
			
		case InclinationCorrection:
			result = almanach.inclinationCorrection();
			break;
			
		case ArgumentPerigee:
			result = almanach.argumentPerigee();
			break;
			
		case AscendingNodeTime:
			result = almanach.ascendingNodeTime();
			break;
			
		case CirculationPeriod:
			result = almanach.circulationPeriod();
			break;
			
		case CirculationVelocity:
			result = almanach.circulationVelocity();
			break;
			
		default:
			break;
	}
	
	return result;
}
