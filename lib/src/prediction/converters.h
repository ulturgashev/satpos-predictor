#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct state_vector {
	double coordinate[3];
	double velocity[3];
} state_vector;

/**
 * @brief ecef2lla ecef wgs84 to lla in meters
 * @param ecef
 * @param lla
 */
void ecef2lla(const double ecef[3], double lla[3]);

/**
 * @brief lla2ecef lla to ecef wgs84 in metters
 * @param lla
 * @param ecef
 */
void lla2ecef(const double lla[3], double ecef[3]);

/**
 * @brief sk_wgs84_pz90 ecef wgs84 to pz90
 * @param inp
 * @param out
 */
void sk_wgs84_pz90(double inp[6], double out[6]);

/**
 * @brief sk_pz90_wgs84 ecef pa90 to wgs84
 * @param inp
 * @param out
 */
void sk_pz90_wgs84(const double inp[6], double out[6]);

#ifdef __cplusplus
}
#endif
