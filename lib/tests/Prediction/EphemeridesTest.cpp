#include <stdio.h>
#include <math.h>

#include <gtest/gtest.h>

#include <Utils.h>

#include "ephemerides.h"

static const double rinexCoordinate[6] = {
	1.452631591797E+04,
	1.205797900391E+04,
	1.717073437500E+04,
	1.045772552490E+00,
	2.103916168213E+00,
	-2.361896514893E+00,
};

static int almanachDayNumber(DateTime dateTime)
{
	const double ti = time_conv(dateTime) + 10800;
	return (int)ti / 86400 + 1;
}

static double defaultTime()
{
	DateTime UTC;
	UTC.YYYY = 2017;
	UTC.MM = 7;
	UTC.DD = 15;
	UTC.hh = 0;
	UTC.mm = 15;
	UTC.ss = 0;

	return time_conv(UTC) + 10800;
}

static glonass_almanach_satellite defaultAlmanach()
{
	DateTime dateTime;
	dateTime.YYYY = 2017;
	dateTime.MM = 7;
	dateTime.DD = 15;

	glonass_almanach_satellite almanach;
	almanach.shiftTime = -0.114440918E-04;
	almanach.inclinationCorrection = 0.6477356E-02;
	almanach.longitude = 0.7687073E+00;
	almanach.eccentricity = 0.4863739E-03;
	almanach.circulationPeriod = -0.2656324E+04;
	almanach.circulationVelocity = 0.1464844E-02;
	almanach.ascendingNodeTime = 0.374169375E+05;
	almanach.argumentPerigee = -0.2214966E+00;
	almanach.fourIntervalNumber = (int)(2017 - 1996) / 4 + 1;
	almanach.almanachDayNumber = almanachDayNumber(dateTime) - (almanach.fourIntervalNumber - 2) * 1461;

	return almanach;
}


TEST(EphemeridesTest, GlonassCoordinate)
{
	double result[6];
	glonass_almanach_satellite almanach = defaultAlmanach();

	calculate_glonass_satellite_position(&almanach, defaultTime() + almanach.shiftTime, result);

	ASSERT_NEAR(result[0], rinexCoordinate[0], 1);
	ASSERT_NEAR(result[1], rinexCoordinate[1], 1);
	ASSERT_NEAR(result[2], rinexCoordinate[2], 1);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

