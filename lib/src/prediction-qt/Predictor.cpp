#include <fstream>

#include "prediction/ephemerides.h"
#include "prediction/geometric.h"

#include "AglStream.h"
#include "CartesianCoordinate.h"
#include "GeodeticCoordinate.h"
#include "PrecisionDateTime.h"
#include "Point3.h"
#include "Prediction.h"
#include "SphericalCoordinate.h"

#include "Predictor.h"

namespace Core
{
	void Predictor::setAlmanachs(const Almanachs &almanachs)
	{
		almanachs_ = almanachs;
	}

	void Predictor::setReceiverCoordinate(const GeodeticCoordinate &coordinate)
	{
		receiverCoordinate_ = coordinate.toCartesianCoordinate();
	}

	std::map<int, Prediction> Predictor::createPredictions(const PrecisionDateTime &dateTime)
	{
		std::map<int, Prediction> result;

		if (!receiverCoordinate_.isNull()) {
			for (const auto &almanach : almanachs_) {
				CartesianCoordinate coordinate = computeSatellitePosition(almanach.second, dateTime);
				result[almanach.first] = computePrediction(coordinate, almanach.second.literNumber());
			}
		}

		return result;
	}

	CartesianCoordinate Predictor::computeSatellitePosition(const Almanach &almanach, const PrecisionDateTime &dateTime) const
	{
		// TODO: Добавить возможность расчета погрешности.
		double vectorCoordinates[6] = {0};
		calculate_glonass_satellite_position(almanach.almanach_.get(), dateTime.glonassTime() + almanach.almanach_->shiftTime, vectorCoordinates);


		return CartesianCoordinate(
				   Point3(vectorCoordinates[0] * 1000, vectorCoordinates[1] * 1000, vectorCoordinates[2] * 1000),
				   Point3(vectorCoordinates[3] * 1000, vectorCoordinates[4] * 1000, vectorCoordinates[5] * 1000)
			   );
	}

	Prediction Predictor::computePrediction(const CartesianCoordinate &targetCoordinate, int literNumber)
	{
		const double source[6] = {receiverCoordinate_.x(), receiverCoordinate_.y(), receiverCoordinate_.z(), 0, 0, 0};
		const double target[6] = {targetCoordinate.x(), targetCoordinate.y(), targetCoordinate.z(), targetCoordinate.vx(), targetCoordinate.vy(), targetCoordinate.vz()};

		return Prediction(compute_geomentric_parameters(source, target), literNumber);
	}

	Almanachs Core::Predictor::readAglFile(const std::string &filename)
	{
		std::fstream fstream(filename);
		std::map<int, Core::Almanach> almanachs;

		if (fstream.is_open()) {
			Core::AglStream stream(fstream);

			while (stream) {
				Core::Almanach almanach;
				stream >> almanach;
				almanachs[almanach.number()] = almanach;
			}
		}

		return almanachs;
	}
}
