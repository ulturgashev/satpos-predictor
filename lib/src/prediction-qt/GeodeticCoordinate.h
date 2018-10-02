#pragma once

class QString;

#include "Point3.h"

namespace Core
{
	class CartesianCoordinate;
	class SphericalCoordinate;

	class GeodeticCoordinate
	{
	public:
		GeodeticCoordinate();
		GeodeticCoordinate(const QString &string);
		GeodeticCoordinate(double latitude, double longitude, double height);

		double latitude() const;
		void setLatitude(double value);

		double longitude() const;
		void setLongitude(double value);

		double height() const;
		void setHeight(double height);

		bool isNull() const;

		CartesianCoordinate toCartesianCoordinate() const;
		SphericalCoordinate toSphericalCoordinate() const;

		QString toString() const;

		constexpr friend bool operator==(const GeodeticCoordinate &lhs, const GeodeticCoordinate &rhs) {
			return (lhs.position_ == rhs.position_);
		}

	private:
		Point3 position_;
	};
}
