#pragma once

#include <QtCore/QSettings>

#include <memory>

#define applicationSettings ApplicationSettings::instance()

class ApplicationSettings
{
public:
	static ApplicationSettings &instance();

	std::map<QString, QVariant> defaultProperties() const;

	/**
	 * @brief Геометрия главного окна приложения.
	 */
	QByteArray mainWindowGeometry() const;
	void setMainWindowGeometry(const QByteArray &geometry);

	/**
	 * @brief Состояние главного окна приложения.
	 */
	QByteArray mainWindowState() const;
	void setMainWindowState(const QByteArray &geometry);

	/**
	 * @brief Угол возвышения.
	 */
	int elevationAngle() const;
	void setElevationAngle(int angle);

	/**
	 * @brief Полный путь к последнему открытому файлу альманаха.
	 */
	QString almanachFilename() const;
	void setAlmanachFilename(const QString &filename);

	/**
	 * @brief Координаты приемника
	 */
	QString receiverCoordinate() const;
	void setReceiverCoordinate(const QString &coordinate);

private:
	ApplicationSettings();
	~ApplicationSettings() = default;
	Q_DISABLE_COPY(ApplicationSettings)

	std::unique_ptr<QSettings> settings() const;

private:
	QString organization_;
	QString applicationName_;
};
