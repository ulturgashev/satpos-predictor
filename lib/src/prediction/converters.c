#include <math.h>

#include "converters.h"

#define SEMIMAJOR_AXIS 6378137.0
#define SEMIMINOR_AXIS 6356752.314245
#define E_ECC 0.0818191
#define WZ 7.2921151467e-5
#define C11 0.48481368E-5

#define PZ_XY  8.20000984E-6
#define PZ     1.0000012
#define WGS_XY 8.19999016E-6
#define WGS    0.9999988

void ecef2lla(const double ecef[3], double lla[3])
{
	const double P = sqrt(ecef[0] * ecef[0] + ecef[1] * ecef[1]);
	const double theta = atan(ecef[2] * SEMIMAJOR_AXIS / (P * SEMIMINOR_AXIS));
	const double sint3 = sin(theta) * sin(theta) * sin(theta);
	const double cost3 = cos(theta) * cos(theta) * cos(theta);

	const double numlat = ecef[2] + ((SEMIMAJOR_AXIS * SEMIMAJOR_AXIS - SEMIMINOR_AXIS * SEMIMINOR_AXIS) / SEMIMINOR_AXIS) * sint3;
	const double denlat = P - E_ECC * E_ECC * SEMIMAJOR_AXIS * cost3;
	const double latitude = atan(numlat / denlat);
	const double longitude = atan2(ecef[1], ecef[0]);

	double Ntemp = 1 - E_ECC * E_ECC * sin(latitude) * sin(latitude);

	double N = 0;

	if (Ntemp < 0.0) {
		N = SEMIMAJOR_AXIS;
	} else {
		N = SEMIMAJOR_AXIS / sqrt(Ntemp);
	}

	const double altitude = P / cos(latitude) - N;

	lla[0] = latitude * 180.0 / M_PI;
	lla[1] = longitude * 180.0 / M_PI;
	lla[2] = altitude;
}

void lla2ecef(const double lla[], double ecef[])
{
	double lat = lla[0] * M_PI / 180.0;
	double lon = lla[1] * M_PI / 180.0;
	double alt = lla[2];

	const double F = 1.0 / 298.257223563; 	// reciprocal flattening
	const double E2 = 2 * F - F * F; // eccentricity squared

	const double chi = sqrt(1 - E2 * sin(lat) * sin(lat));

	ecef[0] = (SEMIMAJOR_AXIS / chi + alt) * cos(lat) * cos(lon);
	ecef[1] = (SEMIMAJOR_AXIS / chi + alt) * cos(lat) * sin(lon);
	ecef[2] = (SEMIMAJOR_AXIS * (1.0 - E2) / chi + alt) * sin(lat);
}

void sk_wgs84_pz90(double inp[6], double out[6])
{

	out[0] = WGS * inp[0] - WGS_XY * inp[1] - 0.0013;
	out[1] = WGS_XY * inp[0] + WGS * inp[1] - 0.0013;
	out[2] = WGS * inp[2] - 0.0009;
	out[3] = WGS * inp[3] - WGS_XY * inp[4];
	out[4] = WGS_XY * inp[3] + WGS * inp[4];
	out[5] = WGS * inp[5];
}

void sk_pz90_wgs84(const double inp[6], double out[6])
{

	out[0] = PZ * inp[0] + PZ_XY * inp[1] + 0.0013;
	out[1] = -PZ_XY * inp[0] + PZ * inp[1] + 0.0013;
	out[2] = PZ * inp[2] + 0.0009;
	out[3] = PZ * inp[3] + PZ_XY * inp[4];
	out[4] = -PZ_XY * inp[3] + PZ * inp[4];
	out[5] = PZ * inp[5];
}
