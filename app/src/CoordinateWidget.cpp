#include "CoordinateWidget.h"
#include "ui_CoordinateWidget.h"

CoordinateWidget::CoordinateWidget(QWidget *parent)
	: QWidget(parent)
	, ui_(new Ui::CoordinateWidget)
{
	ui_->setupUi(this);

	connect(ui_->latitudeLineEdit_, &QLineEdit::textChanged, this, &CoordinateWidget::updateCoordinate);
	connect(ui_->longitudeLineEdit_, &QLineEdit::textChanged, this, &CoordinateWidget::updateCoordinate);
	connect(ui_->heightLineEdit_, &QLineEdit::textChanged, this, &CoordinateWidget::updateCoordinate);
}

CoordinateWidget::~CoordinateWidget() = default;

void CoordinateWidget::setCoordinate(const Core::GeodeticCoordinate &coordinate)
{
	coordinate_ = coordinate;

	ui_->latitudeLineEdit_->setText(QString::number(coordinate.latitude()));
	ui_->longitudeLineEdit_->setText(QString::number(coordinate.longitude()));
	ui_->heightLineEdit_->setText(QString::number(coordinate.height()));
}

Core::GeodeticCoordinate CoordinateWidget::coordinate() const
{
	return coordinate_;
}

void CoordinateWidget::updateCoordinate()
{
	coordinate_ = Core::GeodeticCoordinate(
					  ui_->latitudeLineEdit_->text().toDouble(),
					  ui_->longitudeLineEdit_->text().toDouble(),
					  ui_->heightLineEdit_->text().toDouble()
				  );

	emit coordinateChanged(coordinate_);
}

