#include <iostream>
#include <cmath>

#include <gtest/gtest.h>

#include <Utils.h>

#include "converters.h"

const double ECEF[6] = {310205.00, 3519360.21, 5292542.55, 0, 0, 0};
const double LLA[6] = {56.452627, 84.962828, 100, 0, 0, 0};

namespace
{
	double lenght(const double lhs[], const double rhs[])
	{
		double x = lhs[0] - rhs[0];
		double y = lhs[1] - rhs[1];
		double z = lhs[2] - rhs[2];

		return sqrt(x * x + y * y + z * z);
	}
}

TEST(ConverterTest, TestEcefLlaConverter)
{
	double lla[6] = {0};
	ecef2lla(ECEF, lla);

	ASSERT_LT(lenght(lla, LLA), 0.01);

	double ecef[6] = {0};
	lla2ecef(LLA, ecef);

	ASSERT_LT(lenght(ecef, ECEF), 0.01);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
