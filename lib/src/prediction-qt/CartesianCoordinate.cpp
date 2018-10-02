#include <cmath>

#include "GeodeticCoordinate.h"
#include "SphericalCoordinate.h"

#include "converters.h"

#include "CartesianCoordinate.h"

namespace Core
{
	CartesianCoordinate::CartesianCoordinate()
		: position_()
		, velocity_()
	{
	}

	CartesianCoordinate::CartesianCoordinate(double x, double y, double z)
		: position_(x, y, z)
		, velocity_()
	{
	}

	CartesianCoordinate::CartesianCoordinate(const Point3 &position, const Point3 &velocity)
		: position_(position)
		, velocity_(velocity)
	{
	}

	CartesianCoordinate::CartesianCoordinate(const CartesianCoordinate &other)
	{
		if (*this != other) {
			position_ = other.position_;
			velocity_ = other.velocity_;
		}
	}

	CartesianCoordinate &CartesianCoordinate::operator=(const CartesianCoordinate &other)
	{
		if (*this != other) {
			position_ = other.position_;
			velocity_ = other.velocity_;
		}

		return *this;
	}

	double CartesianCoordinate::x() const
	{
		return position_.x();
	}

	double CartesianCoordinate::y() const
	{
		return position_.y();
	}

	double CartesianCoordinate::z() const
	{
		return position_.z();
	}

	double CartesianCoordinate::vx() const
	{
		return velocity_.x();
	}

	double CartesianCoordinate::vy() const
	{
		return velocity_.y();
	}

	double CartesianCoordinate::vz() const
	{
		return velocity_.z();
	}

	double CartesianCoordinate::length() const
	{
		return position_.length();
	}

	bool CartesianCoordinate::isNull() const
	{
		return position_.isNull();
	}

	GeodeticCoordinate CartesianCoordinate::toGeodeticCoordinate() const
	{
		const double pz90[6] = {position_.x(), position_.y(), position_.z(), velocity_.x(), velocity_.y(), velocity_.z()};
		//		double wgs84[6];
		//		sk_pz90_wgs84(pz90, wgs84);

		double lla[3];
		ecef2lla(pz90, lla);

		return GeodeticCoordinate(lla[0], lla[1], lla[2]);
	}

	SphericalCoordinate CartesianCoordinate::toSphericalCoordinate() const
	{
		constexpr double RAD_TO_DEG = 57.295779513082;

		const double radius = position_.length();
		const double theta = atan2(position_.y(), position_.x()) * RAD_TO_DEG;
		const double phi = atan2(sqrt(position_.x() * position_.x() + position_.y() * position_.y()), position_.z()) * RAD_TO_DEG;

		return SphericalCoordinate(theta, phi, radius);
	}

	CartesianCoordinate &CartesianCoordinate::operator+=(const CartesianCoordinate &other)
	{
		position_ += other.position_;
		velocity_ += other.velocity_;

		return *this;
	}

	CartesianCoordinate &CartesianCoordinate::operator-=(const CartesianCoordinate &other)
	{
		position_ -= other.position_;
		velocity_ -= other.velocity_;

		return *this;
	}
}
