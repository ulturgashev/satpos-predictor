#pragma once

#include <QtCore/QAbstractTableModel>

#include <prediction-qt/Predictor.h>

class AlmanachModel : public QAbstractTableModel
{
	Q_OBJECT

	enum Columns {
		Number,
		Health,
		Date,
		LiterNumber,
		Longitude,
		Eccentricity,
		InclinationCorrection,
		ArgumentPerigee,
		AscendingNodeTime,
		CirculationPeriod,
		CirculationVelocity,
		
		ColumnCount,
	};

public:
	explicit AlmanachModel(QObject *parent = nullptr);
	virtual ~AlmanachModel();

	virtual int rowCount(const QModelIndex &parent) const override;
	virtual int columnCount(const QModelIndex &parent) const override;

	virtual QVariant data(const QModelIndex &index, int role) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	void setAlmanach(const Core::Almanachs &almanachs);
	Core::Almanachs almanachs() const;

private:
	Q_DISABLE_COPY(AlmanachModel)
	
	QVariant almanachDisplayData(const QModelIndex &index) const;

private:
	Core::Almanachs almanachs_;
};
