#include <QtCore/QString>
#include <QtCore/QStringList>

#include <cmath>

#include <prediction/converters.h>

#include "CartesianCoordinate.h"
#include "SphericalCoordinate.h"

#include "GeodeticCoordinate.h"

namespace Core
{
	GeodeticCoordinate::GeodeticCoordinate()
		: position_()
	{
	}

	GeodeticCoordinate::GeodeticCoordinate(const QString &string)
	{
		const QStringList stringList = string.split(';');

		if (stringList.size() == 3) {
			setLatitude(stringList[0].toDouble());
			setLongitude(stringList[1].toDouble());
			setHeight(stringList[2].toDouble());
		}
	}

	GeodeticCoordinate::GeodeticCoordinate(double latitude, double longitude, double height)
		: position_(latitude, longitude, height)
	{
	}

	double GeodeticCoordinate::latitude() const
	{
		return position_.x();
	}

	void GeodeticCoordinate::setLatitude(double value)
	{
		position_.setX(value);
	}

	double GeodeticCoordinate::longitude() const
	{
		return position_.y();
	}

	void GeodeticCoordinate::setLongitude(double value)
	{
		position_.setY(value);
	}

	double GeodeticCoordinate::height() const
	{
		return position_.z();
	}

	void GeodeticCoordinate::setHeight(double height)
	{
		position_.setZ(height);
	}

	bool GeodeticCoordinate::isNull() const
	{
		return position_.isNull();
	}

	CartesianCoordinate GeodeticCoordinate::toCartesianCoordinate() const
	{
		const double lla[3] = {latitude(), longitude(), height()};
		double wgs84[6];
		lla2ecef(lla, wgs84);

		double pz90[6];
		sk_wgs84_pz90(wgs84, pz90);

		return CartesianCoordinate(Point3(pz90[0], pz90[1], pz90[2]), Point3(pz90[3], pz90[4], pz90[5]));
	}

	SphericalCoordinate GeodeticCoordinate::toSphericalCoordinate() const
	{
		// TODO: find implementation of algorithm;
		return SphericalCoordinate();
	}

	QString GeodeticCoordinate::toString() const
	{
		return QString("%1; %2; %3").arg(latitude(), 0, 'g', 15).arg(longitude(), 0, 'g', 15).arg(height(), 0, 'g', 15);
	}
}
