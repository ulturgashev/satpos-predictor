#include <cmath>

#include "CartesianCoordinate.h"
#include "GeodeticCoordinate.h"

#include "SphericalCoordinate.h"

namespace Core
{
	SphericalCoordinate::SphericalCoordinate()
		: position_()
	{
	}

	SphericalCoordinate::SphericalCoordinate(double theta, double phi, double radius)
		: position_(theta, phi, radius)
	{
	}

	double SphericalCoordinate::theta() const
	{
		return position_.x();
	}

	double SphericalCoordinate::phi() const
	{
		return position_.y();
	}

	double SphericalCoordinate::radius() const
	{
		return position_.z();
	}

	bool SphericalCoordinate::isNull() const
	{
		return position_.isNull();
	}

	CartesianCoordinate SphericalCoordinate::toCartesianCoordinate() const
	{
		constexpr double DEG_TO_RAD = 1.7453292519943e-2;

		const double siny = sin(position_.y() * DEG_TO_RAD);
		const double x = position_.z() * siny * cos(position_.x() * DEG_TO_RAD);
		const double y = position_.z() * siny * sin(position_.x() * DEG_TO_RAD);
		const double z = position_.z() * cos(position_.y() * DEG_TO_RAD);

		return CartesianCoordinate(x, y, z);
	}

	GeodeticCoordinate SphericalCoordinate::toGeodeticCoordinate() const
	{
		return GeodeticCoordinate();
	}
}
