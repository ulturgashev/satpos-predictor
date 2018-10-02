#include "ApplicationSettings.h"

namespace
{
	template<typename T, typename... Ts>
	std::unique_ptr<T> make_unique(Ts &&... args)
	{
		return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
	}
}

ApplicationSettings &ApplicationSettings::instance()
{
	static ApplicationSettings settings;
	return settings;
}

std::map<QString, QVariant> ApplicationSettings::defaultProperties() const
{
	static std::map<QString, QVariant> properties = {

	};

	return properties;
}

QByteArray ApplicationSettings::mainWindowGeometry() const
{
	return settings()->value("MainWindow/Geometry").toByteArray();
}

void ApplicationSettings::setMainWindowGeometry(const QByteArray &geometry)
{
	settings()->setValue("MainWindow/Geometry", QVariant(geometry));
}

QByteArray ApplicationSettings::mainWindowState() const
{
	return settings()->value("MainWindow/State").toByteArray();
}

void ApplicationSettings::setMainWindowState(const QByteArray &geometry)
{
	settings()->setValue("MainWindow/State", QVariant(geometry));
}

int ApplicationSettings::elevationAngle() const
{
	return settings()->value("ElevationAngle").toInt();
}

void ApplicationSettings::setElevationAngle(int angle)
{
	settings()->setValue("ElevationAngle", QVariant(angle));
}

QString ApplicationSettings::almanachFilename() const
{
	return settings()->value("AlmanachFilename").toString();
}

void ApplicationSettings::setAlmanachFilename(const QString &filename)
{
	settings()->setValue("AlmanachFilename", QVariant(filename));
}

QString ApplicationSettings::receiverCoordinate() const
{
	return settings()->value("ReceiverCoordinate").toString();
}

void ApplicationSettings::setReceiverCoordinate(const QString &coordinate)
{
	settings()->setValue("ReceiverCoordinate", QVariant(coordinate));
}

ApplicationSettings::ApplicationSettings()
	: organization_("satpos-predictor")
	, applicationName_(APPLICATION_NAME)
{
}

std::unique_ptr<QSettings> ApplicationSettings::settings() const
{
	return make_unique<QSettings>(QSettings::UserScope, organization_, applicationName_);
}
