#pragma once

#include "Point3.h"

#include "GeodeticCoordinate.h"
#include "SphericalCoordinate.h"

namespace Core
{
	class GeodeticCoordinate;
	class SphericalCoordinate;

	class CartesianCoordinate
	{
	public:
		CartesianCoordinate();
		explicit CartesianCoordinate(double x, double y, double z);
		explicit CartesianCoordinate(const Point3 &position, const Point3 &velocity = Point3());

		~CartesianCoordinate() = default;

		CartesianCoordinate(const CartesianCoordinate &other);
		CartesianCoordinate &operator=(const CartesianCoordinate &other);

		double x() const;
		double y() const;
		double z() const;
		double vx() const;
		double vy() const;
		double vz() const;

		double length() const;

		bool isNull() const;

		GeodeticCoordinate toGeodeticCoordinate() const;
		SphericalCoordinate toSphericalCoordinate() const;

		CartesianCoordinate &operator+=(const CartesianCoordinate &other);
		CartesianCoordinate &operator-=(const CartesianCoordinate &other);

		constexpr friend bool operator==(const CartesianCoordinate &lhs, const CartesianCoordinate &rhs) {
			return (lhs.position_ == rhs.position_ && lhs.velocity_ == rhs.velocity_);
		}

		constexpr friend bool operator!=(const CartesianCoordinate &lhs, const CartesianCoordinate &rhs) {
			return !(lhs == rhs);
		}

		friend const CartesianCoordinate operator-(const CartesianCoordinate &lhs, const CartesianCoordinate &rhs) {
			return CartesianCoordinate(Point3(lhs.position_ - rhs.position_), Point3(lhs.velocity_ - rhs.velocity_));
		}

		friend const CartesianCoordinate operator+(const CartesianCoordinate &lhs, const CartesianCoordinate &rhs) {
			return CartesianCoordinate(Point3(lhs.position_ + rhs.position_), Point3(lhs.velocity_ + rhs.velocity_));
		}

	private:
		Point3 position_;
		Point3 velocity_;
	};
}
