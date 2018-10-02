#pragma once


#ifdef __cplusplus
extern "C" {
#endif

// TODO: Плохое название. Переименовать.
typedef struct geometric_parameters {
	double azimuth;      /*!< азимут */
	double elevation;    /*!< угол возвышения */
	double distance;     /*!< расстояние в метрах */
	double velocity;     /*!< скорость */
} geometric_parameters;

geometric_parameters *compute_geomentric_parameters(const double self[], const double target[]);

/**
 * @brief Выделяет память под структуру glonass_almanach_satellite и заполняет нулями;
 */
geometric_parameters *geometric_parameters_new();

/**
 * @brief Освобождение памяти для структуры glonass_almanach_satellite.
 */
void geometric_parameters_free(geometric_parameters *parameters);

#ifdef __cplusplus
}
#endif
