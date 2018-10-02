#pragma once

#include <memory>
#include <iostream>

struct glonass_almanach_satellite;

namespace Core
{
	class PrecisionDateTime;

	class Almanach
	{
		friend class AglStream;
		friend class Predictor;

	public:
		Almanach();
		explicit Almanach(glonass_almanach_satellite *almanach);
		Almanach(const Almanach &other);

		~Almanach();

		Almanach &operator=(const Almanach &other);

		bool isValid() const;

		bool health() const;
		int number() const;
		char literNumber() const;
		unsigned char fourIntervalNumber() const;
		unsigned short almanachDayNumber() const;
		double shiftTime() const;
		double longitude() const;
		double inclinationCorrection() const;
		double eccentricity() const;
		double argumentPerigee() const;
		double ascendingNodeTime() const;
		double circulationPeriod() const;
		double circulationVelocity() const;

	private:
		// TODO: Replace at structure;
		void initialize(const std::string &first, const std::string &second, const std::string &third);

	private:
		std::unique_ptr<glonass_almanach_satellite> almanach_;
	};
}
