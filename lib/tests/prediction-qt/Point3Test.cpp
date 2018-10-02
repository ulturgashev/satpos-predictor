#include <QDebug>

#include <gtest/gtest.h>

#include <Point3.h>

TEST(Point3Test, ConstructorsTest)
{
	Core::Point3 nullPoint;
	ASSERT_TRUE(nullPoint.isNull());

	Core::Point3 point(1.0, 2.0, 3.0);
	ASSERT_FALSE(point.isNull());
}

TEST(Point3Test, LengthTest)
{
	Core::Point3 point(1.0, 0.0, 0.0);
	ASSERT_DOUBLE_EQ(point.length(), 1.0);

	Core::Point3 point1(3.0, -4.0, 0.0);
	ASSERT_DOUBLE_EQ(point1.length(), 5.0);

	Core::Point3 point2(2.0, -4.0, 4.0);
	ASSERT_DOUBLE_EQ(point2.length(), 6.0);
}

TEST(Point3Test, DistanceToPointTest)
{
	Core::Point3 nullPoint;
	Core::Point3 targetPoint(3.0, 4.0, 0.0);

	ASSERT_DOUBLE_EQ(targetPoint.distanceToPoint(nullPoint), 5.0);

	Core::Point3 leftPoint(3.0, 0.0, 10.0);
	Core::Point3 rightPoint(0.0, 4.0, 10.0);

	ASSERT_DOUBLE_EQ(rightPoint.distanceToPoint(leftPoint), 5.0);
}

TEST(Point3Test, SummTest)
{
	Core::Point3 leftPoint(100.0, 100.0, 100.0);
	Core::Point3 rightPoint(100.0, 100.0, 100.0);

	ASSERT_EQ(leftPoint + rightPoint, Core::Point3(200.0, 200.0, 200.0));
}


TEST(Point3Test, SubtractionTest)
{
	Core::Point3 leftPoint(100.0, 100.0, 100.0);
	Core::Point3 rightPoint(100.0, 100.0, 100.0);

	ASSERT_EQ(leftPoint - rightPoint, Core::Point3(0.0, 0.0, 0.0));
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
