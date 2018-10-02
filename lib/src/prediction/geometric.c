#include <math.h>
#include <stdlib.h>

#include "converters.h"

#include "geometric.h"

static void transpose(const double input[][3], double output[][3], int size)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			output[j][i] = input[i][j];
		}
	}
}

static double dot(const double *first, const double *second, int size)
{
	double product = 0.0;

	for (int i = 0; i < size; ++i) {
		product = product + first[i] * second[i];
	}

	return product;
}

static void substruct(const double *first, const double *second, double *output, int size)
{
	for (int i = 0; i < size; ++i) {
		output[i] = first[i] - second[i];
	}
}

static void opposite(const double *input, double *output, int size)
{
	for (int i = 0; i < size; ++i) {
		output[i] = -input[i];
	}
}

static double velocity(const double self[6], const double target[6], double distance)
{
	double selfTarget[3] = {0};
	substruct(self, target, selfTarget, 3);

	double targetSelf[3] = {0};
	opposite(selfTarget, targetSelf, 3);

	const double selfDotProduct = dot(selfTarget, &target[3], 3);
	const double selfVelocity = selfDotProduct / distance;

	const double targetDotProduct = dot(targetSelf, &self[3], 3);
	const double targetVelocity = targetDotProduct / distance;

	return selfVelocity + targetVelocity;
}

geometric_parameters *compute_geomentric_parameters(const double self[], const double target[])
{
	geometric_parameters *parameters = geometric_parameters_new();
	const double deltaTarget[3] = {target[0] - self[0], target[1] - self[1], target[2] - self[2]};

	const double dtr = M_PI / 180.0;

	double lla[6];
	ecef2lla(self, lla);

	const double cb  = cos(lla[0] * dtr);
	const double sb  = sin(lla[0] * dtr);
	const double cl  = cos(lla[1] * dtr);
	const double sl  = sin(lla[1] * dtr);

	const double F[3][3] = {
		{ -sl, -sb * cl, cb * cl},
		{cl, -sb * sl, cb * sl},
		{0, cb, sb}
	};

	double tF[3][3] = {0};

	transpose(F, tF, 3);

	const double E = tF[0][0] * deltaTarget[0] + tF[0][1] * deltaTarget[1] + tF[0][2] * deltaTarget[2];
	const double N = tF[1][0] * deltaTarget[0] + tF[1][1] * deltaTarget[1] + tF[1][2] * deltaTarget[2];
	const double U = tF[2][0] * deltaTarget[0] + tF[2][1] * deltaTarget[1] + tF[2][2] * deltaTarget[2];

	const double hor_dis = sqrt(E * E + N * N);

	if (hor_dis < 1.e-8) {
		parameters->azimuth = 0;
		parameters->elevation = 90;
	} else {
		parameters->azimuth = atan2(E, N) / dtr;
		parameters->elevation = atan2(U, hor_dis) / dtr;
	}

	if (parameters->azimuth < 0) {
		parameters->azimuth = parameters->azimuth + 360;
	}

	parameters->distance = sqrt(deltaTarget[0] * deltaTarget[0] + deltaTarget[1] * deltaTarget[1] + deltaTarget[2] * deltaTarget[2]);
	parameters->velocity = velocity(self, target, parameters->distance);

	return parameters;
}

geometric_parameters *geometric_parameters_new()
{
	return (geometric_parameters *)calloc(1, sizeof(geometric_parameters));
}

void geometric_parameters_free(geometric_parameters *parameters)
{
	free(parameters);
	parameters = NULL;
}
