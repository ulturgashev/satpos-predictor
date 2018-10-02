/**
 * lla to ecef link: http://www.oc.nps.edu/oc2902w/coord/llhxyz.htm
 * ecef to enu link: http://keisan.casio.com/exec/system/1359533867
 */

#include <gtest/gtest.h>

#include <QtCore/QString>

#include <CartesianCoordinate.h>
#include <GeodeticCoordinate.h>
#include <SphericalCoordinate.h>

constexpr auto CARTESIAN_ERROR = 30;
constexpr auto GEODETIC_ERROR = 1.0;
constexpr auto SPHERICAL_ERROR = 1.0;

namespace
{
	void cartesianComparator(const Core::CartesianCoordinate &lhs, const Core::CartesianCoordinate &rhs)
	{
		ASSERT_NEAR(lhs.x(), rhs.x(), CARTESIAN_ERROR);
		ASSERT_NEAR(lhs.y(), rhs.y(), CARTESIAN_ERROR);
		ASSERT_NEAR(lhs.z(), rhs.z(), CARTESIAN_ERROR);
	}

	void geodeticComparator(const Core::GeodeticCoordinate &lhs, const Core::GeodeticCoordinate &rhs)
	{
		ASSERT_NEAR(lhs.longitude(), rhs.longitude(), GEODETIC_ERROR);
		ASSERT_NEAR(lhs.latitude(), rhs.latitude(), GEODETIC_ERROR);
		ASSERT_NEAR(lhs.height(), rhs.height(), GEODETIC_ERROR);
	}

	void sphericalComparator(const Core::SphericalCoordinate &lhs, const Core::SphericalCoordinate &rhs)
	{
		ASSERT_NEAR(lhs.theta(), rhs.theta(), SPHERICAL_ERROR);
		ASSERT_NEAR(lhs.phi(), rhs.phi(), SPHERICAL_ERROR);
		ASSERT_NEAR(lhs.radius(), rhs.radius(), SPHERICAL_ERROR);
	}
}

TEST(CoordinateTest, GeodeticConversionTest)
{
	const Core::CartesianCoordinate cartesian(309666, 3519560, 5292485);
	const Core::GeodeticCoordinate geodetic(56.451210, 84.971823, 136.12);

	sphericalComparator(Core::SphericalCoordinate(84.97, 33.72, 6363457.63), cartesian.toSphericalCoordinate());

	geodeticComparator(geodetic, cartesian.toGeodeticCoordinate());
	cartesianComparator(cartesian, geodetic.toCartesianCoordinate());
}

TEST(CoordinateTest, SerializeToStringTest)
{
	const Core::GeodeticCoordinate defaultCoordinate(56.451210, 84.971823, 136.12);
	const QString geodeticCoordinateString = defaultCoordinate.toString();

	const Core::GeodeticCoordinate restoredCoordinate(geodeticCoordinateString);

	ASSERT_EQ(defaultCoordinate, restoredCoordinate);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
