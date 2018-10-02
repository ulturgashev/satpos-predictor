#pragma once

#include "Point3.h"

namespace Core
{
	class CartesianCoordinate;
	class GeodeticCoordinate;

	class SphericalCoordinate
	{
	public:
		SphericalCoordinate();
		explicit SphericalCoordinate(double theta, double phi, double radius);

		double theta() const;
		double phi() const;
		double radius() const;

		bool isNull() const;

		CartesianCoordinate toCartesianCoordinate() const;
		GeodeticCoordinate toGeodeticCoordinate() const;

	private:
		Point3 position_;
	};
}
