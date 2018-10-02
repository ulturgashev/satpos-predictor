#pragma once


#ifdef __cplusplus
extern "C" {
#endif

/**
* Структура данных альманаха НКА системы ГЛОНАСС
*/
typedef struct glonass_almanach_satellite {
	double shiftTime;                    /*!< Значение_сдвига_шкалы_времени_спутника,сек */
	double longitude;                    /*!< Гринвичская долгота первого восходящего узла,рад */
	double inclinationCorrection;        /*!< Поправка к наклонению орбиты,рад */
	double eccentricity;                 /*!< Эксцентриситет_орбиты_спутника,б/р */
	double argumentPerigee;              /*!< Аргумент_перигея_орбиты_спутника,рад */
	double ascendingNodeTime;            /*!< Время_прохождения_первого_восходящего_узла,c */
	double circulationPeriod;            /*!< Поправка_к_среднему_значению_драконического_периода,c/виток */
	double circulationVelocity;          /*!< Скорость_изменения_периода_обращения,c/виток^2 */
	unsigned short almanachDayNumber;    /*!< номер суток данных альманаха */
	unsigned char fourIntervalNumber;    /*!< Номер четырехлетнего интервала */
	unsigned char type;                  /*!< Признак модификации  НКА */
	unsigned char number;                /*!< Номер НКА */
	unsigned char valid;                 /*!< Признак валидности данных 0 - инвалидные 1 - валидные */
	unsigned char health;                /*!< Признак состояния 0 - спутник нормальный */
	char literNumber;                    /*!< Номер несущей частоты,б/р */
} glonass_almanach_satellite;

/**
 * @brief almanachToPosition Расчет координат спутнка ГЛОНАСС по данным альманаха на заданное время
 * @param almanach альманах НКА ГЛОНАСС
 * @param time расчетное время, с МДВ от 01.01.2000г
 * @param rs расчетный вектор кинематических параметров (X,Y,Z,Vx,Vy,Vz) (км,км/с), в ПЗ-90
 */
void calculate_glonass_satellite_position(const glonass_almanach_satellite *almanach, double time, double *rs);

/**
 * @brief Выделяет память под структуру glonass_almanach_satellite и заполняет нулями
 */
glonass_almanach_satellite *glonass_almanach_satellite_new();

/**
 * @brief Освобождает памяти для структуры glonass_almanach_satellite
 */
void glonass_almanach_satellite_free(glonass_almanach_satellite *almanach);

#ifdef __cplusplus
}
#endif
