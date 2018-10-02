#pragma once

#include <map>

#include "Almanach.h"
#include "CartesianCoordinate.h"
#include "Prediction.h"

namespace Core
{
	class CartesianCoordinate;
	class GeocentricCoordinate;

	using Almanachs = std::map<int, Almanach>;
	using Predictions = std::map<int, Prediction>;

	class Predictor
	{
	public:
		Predictor() = default;
		~Predictor() = default;

		void setAlmanachs(const Almanachs &almanachs);
		void setReceiverCoordinate(const GeodeticCoordinate &coordinate);

		std::map<int, Prediction> createPredictions(const PrecisionDateTime &dateTime);

		static Almanachs readAglFile(const std::string &filename);

	private:
		CartesianCoordinate computeSatellitePosition(const Almanach &almanach, const PrecisionDateTime &dateTime) const;
		Prediction computePrediction(const CartesianCoordinate &targetCoordinate, int literNumber);

	private:
		Almanachs almanachs_;
		CartesianCoordinate receiverCoordinate_;
	};
}
