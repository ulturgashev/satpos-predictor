#include <gtest/gtest.h>

#include "ephemerides.h"
#include "Almanach.h"
#include "CartesianCoordinate.h"
#include "PrecisionDateTime.h"

namespace
{
	glonass_almanach_satellite *makeTestAlmanach()
	{
		glonass_almanach_satellite *almanach = glonass_almanach_satellite_new();
		almanach->health = 1;
		almanach->number = 1;
		almanach->literNumber = 5;

		return almanach;
	}
}

TEST(AlmanachsTest, ConstructorTest)
{
	// TODO: Дописать тест.
	Core::Almanach almanach(makeTestAlmanach());

	ASSERT_EQ(almanach.health(), 1);
	ASSERT_EQ(almanach.number(), 1);
	ASSERT_EQ(almanach.literNumber(), 5);

	Core::Almanach copyAlmanach = almanach;

	ASSERT_EQ(copyAlmanach.health(), 1);
	ASSERT_EQ(copyAlmanach.number(), 1);
	ASSERT_EQ(copyAlmanach.literNumber(), 5);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
