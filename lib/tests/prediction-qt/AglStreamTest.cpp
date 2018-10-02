#include <gtest/gtest.h>

#include <fstream>

#include <Almanach.h>
#include <AglStream.h>

constexpr auto filename = "../../../tests/prediction-qt/samples/MCCJ_170102.agl";

TEST(AglStreamTest, ReadTest)
{
	std::fstream fstream(filename);
	ASSERT_TRUE(fstream.is_open());

	Core::AglStream stream(fstream);
	Core::Almanach almanach;

	stream >> almanach;

	ASSERT_TRUE(almanach.isValid());

	ASSERT_EQ(almanach.number(), 1);
	ASSERT_EQ(almanach.literNumber(), 1);
	ASSERT_EQ(almanach.health(), true);
	ASSERT_DOUBLE_EQ(almanach.ascendingNodeTime(), 0.138943437E+05);
	ASSERT_DOUBLE_EQ(almanach.shiftTime(), -0.762939453E-05);
	ASSERT_DOUBLE_EQ(almanach.longitude(), 0.4139233E+00);
	ASSERT_DOUBLE_EQ(almanach.inclinationCorrection(), 0.6412506E-02);
	ASSERT_DOUBLE_EQ(almanach.argumentPerigee(), 0.1619263E+00);
	ASSERT_DOUBLE_EQ(almanach.eccentricity(), 0.4301071E-03);
	ASSERT_DOUBLE_EQ(almanach.circulationPeriod(), -0.2656264E+04);
	ASSERT_DOUBLE_EQ(almanach.circulationVelocity(), -0.6713867E-03);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
