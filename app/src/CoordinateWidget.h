#pragma once

#include <QtWidgets/QWidget>
#include <prediction-qt/GeodeticCoordinate.h>

#include <memory>

namespace Ui
{
	class CoordinateWidget;
}

class CoordinateWidget : public QWidget
{
	Q_OBJECT

public:
	CoordinateWidget(QWidget *parent = nullptr);
	virtual ~CoordinateWidget();

	void setCoordinate(const Core::GeodeticCoordinate &coordinate);
	Core::GeodeticCoordinate coordinate() const;

signals:
	void coordinateChanged(const Core::GeodeticCoordinate &coordinate);

private:
	Q_DISABLE_COPY(CoordinateWidget)

	void updateCoordinate();

private:
	std::unique_ptr<Ui::CoordinateWidget> ui_;
	Core::GeodeticCoordinate coordinate_;
};
