#include <math.h>
#include <stdlib.h>

#include "ephemerides.h"

#define RE_GLO   6378136.0        /* radius of earth (m)            ref [2] */
#define MU_GPS   3.9860050E14     /* gravitational constant         ref [1] */
#define MU_GLO   3.9860044E14     /* gravitational constant         ref [2] */
#define MU_GAL   3.986004418E14   /* earth gravitational constant   ref [7] */
#define MU_CMP   3.986004418E14   /* earth gravitational constant   ref [9] */
#define J2_GLO   1.0826257E-3     /* 2nd zonal harmonic of geopot   ref [2] */

#define OMGE_GLO 7.292115E-5      /* earth angular velocity (rad/s) ref [2] */
#define OMGE_GAL 7.2921151467E-5  /* earth angular velocity (rad/s) ref [7] */
#define OMGE_CMP 7.292115E-5      /* earth angular velocity (rad/s) ref [9] */

#define SPO 4.3200e+4           // средний период обращения
#define AE  6.378136e+3         // радиус Земли в км. (большая (экваториальная) полуось общеземного эллипсоида)
#define J02 1082.62575e-6       // вторая зональная гармоника геопотенциала
#define MU  398600.4418         // геоцентрическая константа гравитационного поля Земли с учетом атмосферы;
#define WZ 7.2921151467e-5      // угловая скорость вращения Земли
#define H_INT 120               // шаг интегрирования, с

// TODO: UlturgashevVV - Нужно отрефакторить эту функцию.
void calculate_glonass_satellite_position(const glonass_almanach_satellite *alm, double tc, double *vkp)
{
	double ta = (alm->almanachDayNumber + (alm->fourIntervalNumber - 2) * 1461 - 1) * 86400 + alm->ascendingNodeTime;
	// NOTE: Интервал прогноза в секундах времени
	const double tr = tc - ta;

	// NOTE: Определяется количество целых витков W на интервале прогноза
	const double loopCounter = floor(tr / (SPO + alm->circulationPeriod));

	const double inclination = (63 / 180.0 + alm->inclinationCorrection) * M_PI;
	const double cosI = cos(inclination);
	const double sinI = sin(inclination);

	// NOTE: средний драконический период на витке W+1
	const double Tdr = SPO + alm->circulationPeriod + (2 * loopCounter + 1) * alm->circulationVelocity;

	// NOTE: среднее движение:
	double n0 = 2 * M_PI / Tdr;

	// NOTE:  Методом последовательного приближения определяется большая полуось орбиты a
	const double vsp0 = (1.0 - alm->eccentricity * alm->eccentricity);
	const double vsp4 = 1 + alm->eccentricity * cos(alm->argumentPerigee * M_PI);
	const double vsp5 = vsp4 * vsp4;
	const double Tos = 3.0 / 2.0 * J02 * AE * AE * ((2.0 - 2.5 * sinI * sinI) * (vsp0 * sqrt(vsp0)) / vsp5 + vsp5 * vsp4 / vsp0);
	const double mu0 = MU / (4 * M_PI * M_PI);

	double an0 = 0.0;
	double an = pow(mu0 * Tdr * Tdr, 1. / 3.);
	double pn = an * vsp0;

	while (fabs(an0 - an) > 1e-7) {
		an0 = an;
		double Tosc = Tdr / (1 - Tos / (pn * pn));
		an = pow(mu0 * Tosc * Tosc, 1. / 3.);
		pn = an * vsp0;
	}

	// NOTE: Определяется текущие значения долготы восходящего узла орбиты и аргумента перигея с учетом их векового движения под влиянием сжатия Земли:
	ta += Tdr * loopCounter + alm->circulationVelocity * loopCounter * loopCounter;

	double ae_p = AE / pn;
	ae_p = ae_p * ae_p * (3.0 / 2.0) * J02 * n0;

	double lambda_k = alm->longitude * M_PI - (WZ + ae_p * cosI) * tr;
	double omega = alm->argumentPerigee * M_PI - 0.5 * ae_p * (1. - 5. * cosI * cosI) * tr;

	// NOTE: Определяется значение средней долготы на момент прохождения текущего восходящего узла:
	double E0 = -2 * atan(sqrt((1 - alm->eccentricity) / (1 + alm->eccentricity)) * tan(omega / 2.0));
	double L1 = omega + E0 - alm->eccentricity * sin(E0);

	// NOTE:  Определяется текущее значение средней долготы КА
	double L2 = L1 + n0 * (tr - (SPO + alm->circulationPeriod) * loopCounter - alm->circulationVelocity * loopCounter * loopCounter);

	// NOTE: корректируются с учетом периодических возмущений от сжатия Земли по формулам:

	double BB = AE / an;
	BB = (3.0 / 2.0) * J02 * BB * BB;
	double BB1 = BB * (1 - (3.0 / 2.0 * sinI * sinI));
	double BB2 = BB * sinI * sinI;
	double BB3 = BB * cosI * cosI;
	double h = alm->eccentricity * sin(omega);
	double l = alm->eccentricity * cos(omega);

	double da1 = 2 * BB1 * (l * cos(L1) + h * sin(L1)) + BB2 * (0.5 * h * sin(L1) - 0.5 * l * cos(L1) + cos(2 * L1) + 3.5 * l * cos(3 * L1) + 3.5 * h * sin(
					 3 * L1));
	double da2 = 2 * BB1 * (l * cos(L2) + h * sin(L2)) + BB2 * (0.5 * h * sin(L2) - 0.5 * l * cos(L2) + cos(2 * L2) + 3.5 * l * cos(3 * L2) + 3.5 * h * sin(
					 3 * L2));
	double anD = an * (1 + da2 - da1);


	double dh1 = BB1 * (sin(L1) + 1.5 * l * sin(2 * L1) - 1.5 * h * cos(2 * L1)) - 0.25 * BB2 *
				 (sin(L1) - (7. / 3.) * sin(3 * L1) + 5.*l * sin(2 * L1) - 8.5 * l * sin(4 * L1) + 8.5 * h * cos(4 * L1) + h * cos(2 * L1)) +
				 (-0.5 * BB3 * l * sin(2 * L1));
	double dh2 = BB1 * (sin(L2) + 1.5 * l * sin(2 * L2) - 1.5 * h * cos(2 * L2)) - 0.25 * BB2 *
				 (sin(L2) - (7. / 3.) * sin(3 * L2) + 5.*l * sin(2 * L2) - 8.5 * l * sin(4 * L2) + 8.5 * h * cos(4 * L2) + h * cos(2 * L2)) +
				 (-0.5 * BB3 * l * sin(2 * L2));

	double hD = h + dh2 - dh1;

	double dl1 = BB1 * (cos(L1) + 1.5 * l * cos(2 * L1) + 1.5 * h * sin(2 * L1)) - 0.25 * BB2 *
				 (-cos(L1) - (7. / 3.) * cos(3 * L1) - 5.*h * sin(2 * L1) - 8.5 * l * cos(4 * L1) - 8.5 * h * sin(4 * L1) + l * cos(2 * L1)) +
				 (0.5 * BB3 * h * sin(2 * L1));
	double dl2 = BB1 * (cos(L2) + 1.5 * l * cos(2 * L2) + 1.5 * h * sin(2 * L2)) - 0.25 * BB2 *
				 (-cos(L2) - (7. / 3.) * cos(3 * L2) - 5.*h * sin(2 * L2) - 8.5 * l * cos(4 * L2) - 8.5 * h * sin(4 * L2) + l * cos(2 * L2)) +
				 (0.5 * BB3 * h * sin(2 * L2));

	double lD = l + dl2 - dl1;

	double epsD = sqrt(hD * hD + lD * lD);

	double di1 = 0.5 * BB * sinI * cosI * (-l * cos(L1) + h * sin(L1) + cos(2 * L1) + (7. / 3.) * l * cos(3 * L1) + (7. / 3.) * h * sin(3 * L1));
	double di2 = 0.5 * BB * sinI * cosI * (-l * cos(L2) + h * sin(L2) + cos(2 * L2) + (7. / 3.) * l * cos(3 * L2) + (7. / 3.) * h * sin(3 * L2));

	double iD = inclination + di2 - di1;

	double dlam1 = -BB * cosI * (3.5 * l * sin(L1) - 2.5 * h * cos(L1) - 0.5 * sin(2 * L1) - (7. / 6.) * l * sin(3 * L1) + (7. / 6.) * h * cos(3 * L1));
	double dlam2 = -BB * cosI * (3.5 * l * sin(L2) - 2.5 * h * cos(L2) - 0.5 * sin(2 * L2) - (7. / 6.) * l * sin(3 * L2) + (7. / 6.) * h * cos(3 * L2));

	double lamD = lambda_k + dlam2 - dlam1;

	double dL1 = 2 * BB1 * ((7. / 4.) * l * sin(L1) - (7. / 4.) * h * cos(L1)) + 3 * BB2 * (-(7. / 24.) * h * cos(L1) - (7. / 24.) * l * sin(L1) -
				 (49. / 72.) * h * cos(3 * L1) + (49. / 72.) * l * sin(3 * L1) + 0.25 * sin(2 * L1))
				 + BB3 * (3.5 * l * sin(L1) - 2.5 * h * cos(L1) - 0.5 * sin(2 * L1) + (7. / 6.) * l * sin(3 * L1) + (7. / 6.) * h * cos(3 * L1));
	double dL2 = 2 * BB1 * ((7. / 4.) * l * sin(L2) - (7. / 4.) * h * cos(L2)) + 3 * BB2 * (-(7. / 24.) * h * cos(L2) - (7. / 24.) * l * sin(L2) -
				 (49. / 72.) * h * cos(3 * L2) + (49. / 72.) * l * sin(3 * L2) + 0.25 * sin(2 * L2))
				 + BB3 * (3.5 * l * sin(L2) - 2.5 * h * cos(L2) - 0.5 * sin(2 * L2) + (7. / 6.) * l * sin(3 * L2) + (7. / 6.) * h * cos(3 * L2));

	double LD = L2 + dL2 - dL1;

	double omegaD = 0.0;

	if (fabs(lD) > 1E-15) {
		omegaD = atan(hD / lD);
	} else if (hD > 1E-15) {
		omegaD = M_PI_2;
	} else if (hD < -1E-15) {
		omegaD = -M_PI_2;
	}

	// NOTE: Определяется эксцентрическая аномалия :
	double E1 = LD - omegaD;
	double E2 = E1 + epsD * sin(E1);

	while (fabs(E2 - E1) > 1E-11) {
		E1 = E2;
		E2 = LD - omegaD + epsD * sin(E1);
	}

	// NOTE: Определяется истинная аномалия v и аргумент широты КА u:
	double v_i = 2 * atan(sqrt((1.0 + epsD) / (1.0 - epsD)) * tan(E2 / 2.0));
	double u_i = v_i + omegaD;

	// NOTE: Определяются гринвичские координаты КА:
	double p = anD * (1.0 - epsD * epsD);
	double r = p / (1.0 + epsD * cos(v_i));
	vkp[0] = r * (cos(lamD) * cos(u_i) - sin(lamD) * sin(u_i) * cos(iD)); //x
	vkp[1] = r * (sin(lamD) * cos(u_i) + cos(lamD) * sin(u_i) * cos(iD)); //y
	vkp[2] = r * sin(u_i) * sin(iD);                                //z

	// NOTE: компоненты вектора скорости в Гринвичской системе координат
	p = sqrt(MU / p);
	double vr = p * epsD * sin(v_i);
	double vu = p * (1 + epsD * cos(v_i));

	vkp[3] = vr * (cos(lamD) * cos(u_i) - sin(lamD) * sin(u_i) * cos(iD)) - vu * (cos(lamD) * sin(u_i) + sin(lamD) * cos(u_i) * cos(iD)) + WZ * vkp[1];
	vkp[4] = vr * (sin(lamD) * cos(u_i) + cos(lamD) * sin(u_i) * cos(iD)) - vu * (sin(lamD) * sin(u_i) - cos(lamD) * cos(u_i) * cos(iD)) - WZ * vkp[0];
	vkp[5] = vr * sin(u_i) * sin(iD) + vu * cos(u_i) * sin(iD);
}

glonass_almanach_satellite *glonass_almanach_satellite_new()
{
	glonass_almanach_satellite *almanach = (glonass_almanach_satellite *)calloc(1, sizeof(glonass_almanach_satellite));
	return almanach;
}

void glonass_almanach_satellite_free(glonass_almanach_satellite* almanach)
{
	free(almanach);
	almanach = NULL;
}
