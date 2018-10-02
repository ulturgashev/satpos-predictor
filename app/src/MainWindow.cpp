#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QDateTime>
#include <QtCore/QTimeZone>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QToolButton>

#include "prediction-qt/Predictor.h"
#include "prediction-qt/PrecisionDateTime.h"

#include "ApplicationSettings.h"
#include "AlmanachModel.h"
#include "PredictionModel.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace
{
	QDateTime mdtDateTime(const QDateTime &dateTime)
	{
		return dateTime.addSecs(-10800 - 3600);
	}
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui_(new Ui::MainWindow)
	, almanachModel_(new AlmanachModel(this))
	, predictionModel_(new PredictionModel(this))
	, predictor_(new Core::Predictor())
	, timer_(new QTimer(this))
{
	ui_->setupUi(this);

	ui_->almanachTableView_->setModel(almanachModel_);
	ui_->predictionTableView_->setModel(predictionModel_);

	connect(timer_, &QTimer::timeout, this, &MainWindow::updatePrediction);
	connect(ui_->openAlmanachToolButton_, &QToolButton::clicked, this, &MainWindow::openAglFile);

	connect(ui_->autoUpdateCheckBox_, &QCheckBox::clicked, this, &MainWindow::updateControl);
	connect(ui_->autoUpdateCheckBox_, &QCheckBox::clicked, this, &MainWindow::timerControl);

	connect(ui_->almanachPathLineEdit_, SIGNAL(textChanged(QString)), SLOT(updateAlmanach()));
	connect(ui_->elevationSpinBox_, SIGNAL(valueChanged(int)), SLOT(updateElevationAngle()));
	connect(ui_->autoUpdateSpinBox_, SIGNAL(valueChanged(int)), this, SLOT(timerControl()));
	connect(ui_->coordinateWidget_, SIGNAL(coordinateChanged(Core::GeodeticCoordinate)), SLOT(updateReceiverCoordinate(Core::GeodeticCoordinate)));
	connect(ui_->calculatePushButton_, SIGNAL(clicked()), SLOT(predict()));

	ui_->estimatedDateTimeEdit_->setDateTime(QDateTime::currentDateTime());

	loadWindowSettings();
	updateControl();
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent *event)
{
	saveWindowSettings();
	QMainWindow::closeEvent(event);
}

void MainWindow::openAglFile()
{
	const QString filename = getAglFilename();

	if (!filename.isEmpty()) {
		ui_->almanachPathLineEdit_->setText(filename);
	}
}

void MainWindow::updatePrediction()
{
	ui_->estimatedDateTimeEdit_->setDateTime(QDateTime::currentDateTime());
	predict();
}

void MainWindow::timerControl()
{
	if (ui_->autoUpdateCheckBox_->isChecked()) {
		timer_->start(ui_->autoUpdateSpinBox_->value() * 1000);
	} else {
		timer_->stop();
	}
}

void MainWindow::predict()
{
	predictionModel_->setPredictions(predictor_->createPredictions(Core::PrecisionDateTime(mdtDateTime(ui_->estimatedDateTimeEdit_->dateTime()))));
}

void MainWindow::updateAlmanach()
{
	const auto almanachs = Core::Predictor::readAglFile(ui_->almanachPathLineEdit_->text().toStdString());
	almanachModel_->setAlmanach(almanachs);
	predictor_->setAlmanachs(almanachs);
	predictionModel_->setAlmanach(almanachs);
}

void MainWindow::updateElevationAngle()
{
	predictionModel_->setElevationAngle(ui_->elevationSpinBox_->value());
	predict();
}

void MainWindow::updateReceiverCoordinate(const Core::GeodeticCoordinate &coordinate)
{
	predictor_->setReceiverCoordinate(coordinate);
	applicationSettings.setReceiverCoordinate(coordinate.toString());
}

void MainWindow::updateControl()
{
	const bool autoUpdateEnable = ui_->autoUpdateCheckBox_->isChecked();

	ui_->autoUpdateSpinBox_->setEnabled(autoUpdateEnable);
	ui_->calculatePushButton_->setDisabled(autoUpdateEnable);
	ui_->estimatedDateTimeEdit_->setDisabled(autoUpdateEnable);
}

QString MainWindow::getAglFilename()
{
	return QFileDialog::getOpenFileName(this, tr("Open file"), "/home", tr("Agl (*.agl *agl.txt)"));
}

void MainWindow::loadWindowSettings()
{
	restoreGeometry(applicationSettings.mainWindowGeometry());
	restoreState(applicationSettings.mainWindowState());

	ui_->elevationSpinBox_->setValue(applicationSettings.elevationAngle());
	ui_->almanachPathLineEdit_->setText(applicationSettings.almanachFilename());
	ui_->coordinateWidget_->setCoordinate(Core::GeodeticCoordinate(applicationSettings.receiverCoordinate()));
}

void MainWindow::saveWindowSettings() const
{
	applicationSettings.setMainWindowGeometry(saveGeometry());
	applicationSettings.setMainWindowState(saveState());

	applicationSettings.setElevationAngle(ui_->elevationSpinBox_->value());
	applicationSettings.setAlmanachFilename(ui_->almanachPathLineEdit_->text());
	applicationSettings.setReceiverCoordinate(ui_->coordinateWidget_->coordinate().toString());
}

