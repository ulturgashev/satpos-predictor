#include <cmath>

#include "Point3.h"

namespace Core
{
	double Point3::x() const
	{
		return x_;
	}

	void Point3::setX(double value)
	{
		x_ = value;
	}

	double Point3::y() const
	{
		return y_;
	}

	void Point3::setY(double value)
	{
		y_ = value;
	}

	double Point3::z() const
	{
		return z_;
	}

	void Point3::setZ(double value)
	{
		z_ = value;
	}

	double Point3::distanceToPoint(const Point3 &target)
	{
		return (*this - target).length();
	}

	bool Point3::isNull() const
	{
		return (x_ == 0.0 && y_ == 0.0 && z_ == 0.0);
	}

	double Point3::length() const
	{
		return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
	}

	std::array<double, 3> Point3::values() const
	{
		return std::array<double, 3>({x_, y_, z_});
	}

	Point3 &Point3::operator+=(const Point3 &other)
	{
		x_ += other.x_;
		y_ += other.y_;
		z_ += other.z_;

		return *this;
	}

	Point3 &Point3::operator-=(const Point3 &other)
	{
		x_ -= other.x_;
		y_ -= other.y_;
		z_ -= other.z_;

		return *this;
	}
}
