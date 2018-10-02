#pragma once

#include <memory>

struct geometric_parameters;

namespace Core
{
	class Prediction
	{
	public:
		Prediction();
		explicit Prediction(geometric_parameters *parameters, int literNumber);
		Prediction(const Prediction &other);

		~Prediction();
		
		Prediction &operator=(const Prediction &other);

		double azimuth() const;
		double elevation() const;
		double doppler() const;
		double distance() const;

	private:
		std::unique_ptr<geometric_parameters> parameters_;
		double doppler_;
	};
}
