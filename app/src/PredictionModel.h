#pragma once

#include <QtCore/QAbstractTableModel>

#include <prediction-qt/Predictor.h>

namespace Core
{
	using Predictions = std::map<int, Prediction>;
}

class PredictionModel : public QAbstractTableModel
{
	Q_OBJECT

	enum Columns {
		Number,
		LiterNumber,
		Azimuth,
		Elevation,
		Doppler,
		Distance,

		ColumnCount,
	};

public:
	explicit PredictionModel(QObject *parent = nullptr);
	virtual ~PredictionModel();

	virtual int rowCount(const QModelIndex &parent) const override;
	virtual int columnCount(const QModelIndex &parent) const override;

	virtual QVariant data(const QModelIndex &index, int role) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	void setAlmanach(const Core::Almanachs &almanachs);
	void setPredictions(const Core::Predictions &predictions);
	void setElevationAngle(double angle);

private:
	Q_DISABLE_COPY(PredictionModel)

	QVariant predictionDisplayData(const QModelIndex &index) const;
	QVariant backgroundColor(const QModelIndex &index) const;

private:
	Core::Almanachs almanachs_;
	Core::Predictions predictions_;
	double elevationAngle_;
};
