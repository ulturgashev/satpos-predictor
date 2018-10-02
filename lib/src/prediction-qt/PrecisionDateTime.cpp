#include "PrecisionDateTime.h"

constexpr auto GLONASS_TIME_OFFSET = 946659600;

namespace Core
{
	PrecisionDateTime::PrecisionDateTime(double time)
		: dateTime_(QDateTime::fromMSecsSinceEpoch(time))
		, offset_(0.0)
	{

	}

	PrecisionDateTime::PrecisionDateTime(const QDateTime &dateTime, double offset)
		: dateTime_(dateTime)
		, offset_(offset)
	{
	}

	double PrecisionDateTime::glonassTime() const
	{
		const quint64 msec = dateTime_.toMSecsSinceEpoch();
		return msec / 1000 - GLONASS_TIME_OFFSET + offset_;
	}
}
