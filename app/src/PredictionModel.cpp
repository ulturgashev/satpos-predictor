#include <QtGui/QColor>

#include <prediction-qt/Prediction.h>

#include "PredictionModel.h"

namespace
{
	template<typename Key, typename Value>
	Value getMapValue(const std::map<Key, Value> &map, const Key &key, const Value &defaultValue = Value())
	{
		const auto it = map.find(key);
		return (it == map.cend()) ? defaultValue : it->second;
	}
}

PredictionModel::PredictionModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

PredictionModel::~PredictionModel() = default;

int PredictionModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return predictions_.size();
}

int PredictionModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return ColumnCount;
}

QVariant PredictionModel::data(const QModelIndex &index, int role) const
{
	QVariant result;

	if (index.isValid()) {
		switch (role) {
			case Qt::DisplayRole:
				result = predictionDisplayData(index);
				break;

			case Qt::TextAlignmentRole:
				result = QVariant(Qt::AlignLeft | Qt::AlignVCenter);
				break;

			case Qt::BackgroundColorRole:
				result = backgroundColor(index);

			default:
				break;
		}
	}

	return result;
}

QVariant PredictionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	static const std::map<int, QString> headers = {
		{Number, tr("Number")},
		{LiterNumber, tr("Liter number")},
		{Azimuth, tr("Azimuth")},
		{Elevation, tr("Elevation")},
		{Doppler, tr("Doppler")},
		{Distance, tr("Distance")},
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

void PredictionModel::setAlmanach(const Core::Almanachs &almanachs)
{
	beginResetModel();
	almanachs_ = almanachs;
	endResetModel();
}

void PredictionModel::setPredictions(const Core::Predictions &predictions)
{
	beginResetModel();
	predictions_ = predictions;
	endResetModel();
}

void PredictionModel::setElevationAngle(double angle)
{
	elevationAngle_ = angle;
}

QVariant PredictionModel::predictionDisplayData(const QModelIndex &index) const
{
	QVariant result;

	const Core::Prediction prediction = getMapValue(predictions_, index.row() + 1);

	switch (index.column()) {
		case Number:
			result = index.row() + 1;
			break;

		case LiterNumber:
			result = getMapValue(almanachs_, index.row() + 1).literNumber();
			break;

		case Azimuth:
			result = prediction.azimuth();
			break;

		case Elevation:
			result = prediction.elevation();
			break;

		case Distance:
			result = QString::number(prediction.distance(), 'g', 15);
			break;

		case Doppler:
			result = QString::number(prediction.doppler(), 'g', 15);
			break;

		default:
			break;
	}

	return result;
}

QVariant PredictionModel::backgroundColor(const QModelIndex &index) const
{
	const Core::Prediction prediction = getMapValue(predictions_, index.row() + 1);
	return (elevationAngle_ < prediction.elevation()) ? QColor("#80ff80") : QColor("#ff8080");
}

