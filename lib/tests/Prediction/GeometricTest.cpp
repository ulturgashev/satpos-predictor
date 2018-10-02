#include <iostream>

#include <gtest/gtest.h>

#include "geometric.h"

TEST(GeometricTest, ComputeGeometricParameters)
{
	const double self[3] = {3000, 3000, 0};
	const double target[] = {0, 6000, 0};

	geometric_parameters *parameters = compute_geomentric_parameters(self, target);

	ASSERT_EQ(90, parameters->azimuth);
	ASSERT_LT(parameters->elevation, 0.00001);

	geometric_parameters_free(parameters);

	const double self1[3] = {0, 6400000.0, 0};
	const double target1[3] = {0, 60000000.0, 0};

	geometric_parameters *parameters1 = compute_geomentric_parameters(self1, target1);

	ASSERT_EQ(0, parameters1->azimuth);
	ASSERT_EQ(90, parameters1->elevation);

	geometric_parameters_free(parameters1);

	const double self2[3] = {3000, 6378137, 3000};
	const double target2[3] = {3000, 6378137 + 200, 3000};

	geometric_parameters *parameters2 = compute_geomentric_parameters(self2, target2);

	ASSERT_NEAR(parameters2->azimuth, 135.192, 0.001);
	ASSERT_NEAR(parameters2->elevation, 89.961, 0.001);
	ASSERT_NEAR(parameters2->distance, 200, 0.001);

	geometric_parameters_free(parameters2);

	const double self3[3] = {3000, 6378137, 3000};
	const double target3[3] = {3000 + 1000, 6378137, 3000 + 100};

	geometric_parameters *parameters3 = compute_geomentric_parameters(self3, target3);

	ASSERT_NEAR(parameters3->azimuth, 275.71, 0.001);
	ASSERT_NEAR(parameters3->elevation, 0.029, 0.001);
	ASSERT_NEAR(parameters3->distance, 1005, 0.1);

	geometric_parameters_free(parameters3);
}

TEST(GeometricTest, VelocityTest)
{
	const double self1[6] = {30, 0, 0, 1, 0, 0};
	const double target1[6] = {40, 0, 0, -1, 0, 0};

	geometric_parameters *parameters1 = compute_geomentric_parameters(self1, target1);

	ASSERT_EQ(parameters1->velocity, 2.0);

	geometric_parameters_free(parameters1);

	const double self2[6] = {30, 0, 0, 0, 10, 0};
	const double target2[6] = {40, 0, 0, 0, 10, 0};

	geometric_parameters *parameters2 = compute_geomentric_parameters(self2, target2);

	ASSERT_EQ(parameters2->velocity, 0.0);

	geometric_parameters_free(parameters2);

	const double self3[6] = {30, 0, 0, 1, 1, 0};
	const double target3[6] = {40, 0, 0, 1, 1, 0};

	geometric_parameters *parameters3 = compute_geomentric_parameters(self3, target3);

	ASSERT_EQ(parameters3->velocity, 0.0);

	geometric_parameters_free(parameters3);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

