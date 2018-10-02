#pragma once

#include <QtWidgets/QMainWindow>

#include <memory>

class AlmanachModel;
class PredictionModel;

namespace Ui
{
	class MainWindow;
}

namespace Core
{
	class GeodeticCoordinate;
	class Predictor;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	virtual ~MainWindow();

protected:
	virtual void closeEvent(QCloseEvent *event) override;

private slots:
	void openAglFile();
	// TODO: Переименовать.
	void updatePrediction();
	void timerControl();
	void predict();
	void updateAlmanach();
	void updateElevationAngle();
	void updateReceiverCoordinate(const Core::GeodeticCoordinate &coordinate);
	void updateControl();

private:
	QString getAglFilename();

	void loadWindowSettings();
	void saveWindowSettings() const;

private:
	std::unique_ptr<Ui::MainWindow> ui_;
	AlmanachModel *almanachModel_;
	PredictionModel *predictionModel_;

	std::unique_ptr<Core::Predictor> predictor_;

	QTimer *timer_;
};
