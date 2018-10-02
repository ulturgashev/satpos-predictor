#pragma once

#include <QtCore/QDateTime>

namespace Core
{
	class PrecisionDateTime
	{
	public:
		/**
		 * @brief PrecisionDateTime
		 * @param time
		 * Время в секундах от 1970 года.
		 */
		explicit PrecisionDateTime(double time);

		/**
		 * @brief PrecisionDateTime
		 * @param dateTime
		 * @param offset - смещение в секундах
		 */
		explicit PrecisionDateTime(const QDateTime &dateTime, double offset = 0.0);

		~PrecisionDateTime() = default;

		double glonassTime() const;

	private:
		QDateTime dateTime_;
		double offset_;
	};
}
