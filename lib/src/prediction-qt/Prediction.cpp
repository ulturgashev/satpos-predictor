#include "prediction/geometric.h"

#include "Prediction.h"

constexpr auto CARRIER_FREQUENCY = 1602 * 1000 * 1000;
constexpr auto SHIFT_FREQUENCY = 562.5 * 1000;
constexpr auto SPEED_LIGHT = 299792458;

namespace Core
{
	Prediction::Prediction()
		: Prediction(geometric_parameters_new(), 0)
	{
	}

	Prediction::Prediction(geometric_parameters *parameters, int literNumber)
		: parameters_(parameters)
	{
		const double frequency = CARRIER_FREQUENCY + literNumber * SHIFT_FREQUENCY;
		// TODO: May be need add relativistic correction.
		doppler_ = parameters_->velocity * frequency / SPEED_LIGHT;
	}

	Prediction::Prediction(const Prediction &other)
		: parameters_(geometric_parameters_new())
	{
		*parameters_ = *other.parameters_;
		doppler_ = other.doppler_;
	}

	Prediction::~Prediction() = default;

	Prediction &Prediction::operator=(const Prediction &other)
	{
		if (this != &other) {
			*parameters_ = *other.parameters_;
			doppler_ = other.doppler_;
		}

		return *this;
	}

	double Prediction::azimuth() const
	{
		return parameters_->azimuth;
	}

	double Prediction::elevation() const
	{
		return parameters_->elevation;
	}

	double Prediction::doppler() const
	{
		return doppler_;
	}

	double Prediction::distance() const
	{
		return parameters_->distance;
	}
}
