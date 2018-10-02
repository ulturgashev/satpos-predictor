#include <map>
#include <sstream>

#include <QtCore/QString>

#include "prediction/ephemerides.h"

#include "PrecisionDateTime.h"

#include "Almanach.h"

constexpr auto SECOND_LINE_WORD_COUNT = 10;
constexpr auto THIRD_LINE_WORD_COUNT = 6;
constexpr auto BEGIN_FOURTH_INTERVAL = 1996;

namespace
{
	int computeAlmanachDayNumber(int year, int month, int day)
	{
		Core::PrecisionDateTime dateTime(QDateTime(QDate(year, month, day)));
		return static_cast<int>(dateTime.glonassTime()) / 86400 + 1;
	}

	bool parsingSecondLine(glonass_almanach_satellite *almanach, const std::string &string)
	{
		bool result = false;

		std::istringstream stringStream(string);

		std::vector<std::string> words;
		words.reserve(SECOND_LINE_WORD_COUNT);

		std::string temp;

		for (int i = 0; stringStream >> temp; ++i) {
			words.push_back(temp);
		}

		if (words.size() == SECOND_LINE_WORD_COUNT) {
			almanach->number = atoi(words[0].c_str());
			almanach->literNumber = atoi(words[1].c_str());
			almanach->health = atoi(words[2].c_str());
			almanach->valid = almanach->health;

			const int year = atoi(words[5].c_str());

			almanach->fourIntervalNumber = (int)(year - BEGIN_FOURTH_INTERVAL) / 4 + 1;
			almanach->almanachDayNumber = computeAlmanachDayNumber(year, atoi(words[4].c_str()), atoi(words[3].c_str())) - (almanach->fourIntervalNumber - 2) * 1461;

			almanach->ascendingNodeTime = QString(words[6].c_str()).toDouble();
			almanach->shiftTime = QString(words[9].c_str()).toDouble();

			result = true;
		}

		return result;
	}

	bool parsingThirdLine(glonass_almanach_satellite *almanach, const std::string &string)
	{
		bool result;

		std::istringstream stringStream(string);

		std::vector<std::string> words;
		words.reserve(THIRD_LINE_WORD_COUNT);

		std::string temp;

		for (int i = 0; stringStream >> temp; ++i) {
			words.push_back(temp);
		}

		if (words.size() == THIRD_LINE_WORD_COUNT) {
			almanach->longitude = QString(words[0].c_str()).toDouble();
			almanach->inclinationCorrection = QString(words[1].c_str()).toDouble();
			almanach->argumentPerigee = QString(words[2].c_str()).toDouble();
			almanach->eccentricity = QString(words[3].c_str()).toDouble();
			almanach->circulationPeriod = QString(words[4].c_str()).toDouble();
			almanach->circulationVelocity = QString(words[5].c_str()).toDouble();

			result = true;
		}

		return result;
	}
}

namespace Core
{
	Almanach::Almanach()
		: Almanach(glonass_almanach_satellite_new())
	{
	}

	Almanach::Almanach(glonass_almanach_satellite *almanach)
		: almanach_(almanach)
	{
	}

	Almanach::Almanach(const Almanach &other)
		: Almanach()
	{
		if (this != &other) {
			*almanach_ = *other.almanach_;
		}
	}

	Almanach::~Almanach() = default;

	Almanach &Almanach::operator=(const Almanach &other)
	{
		if (this != &other) {
			*almanach_ = *other.almanach_;
		}

		return *this;
	}

	bool Almanach::isValid() const
	{
		return almanach_->valid;
	}

	bool Almanach::health() const
	{
		return almanach_->health;
	}

	int Almanach::number() const
	{
		return almanach_->number;
	}

	char Almanach::literNumber() const
	{
		return almanach_->literNumber;
	}

	unsigned char Almanach::fourIntervalNumber() const
	{
		return almanach_->fourIntervalNumber;
	}

	unsigned short Almanach::almanachDayNumber() const
	{
		return almanach_->almanachDayNumber;
	}

	double Almanach::shiftTime() const
	{
		return almanach_->shiftTime;
	}

	double Almanach::longitude() const
	{
		return almanach_->longitude;
	}

	double Almanach::inclinationCorrection() const
	{
		return almanach_->inclinationCorrection;
	}

	double Almanach::eccentricity() const
	{
		return almanach_->eccentricity;
	}

	double Almanach::argumentPerigee() const
	{
		return almanach_->argumentPerigee;
	}

	double Almanach::ascendingNodeTime() const
	{
		return almanach_->ascendingNodeTime;
	}

	double Almanach::circulationPeriod() const
	{
		return almanach_->circulationPeriod;
	}

	double Almanach::circulationVelocity() const
	{
		return almanach_->circulationVelocity;
	}

	void Almanach::initialize(const std::string &first, const std::string &second, const std::string &third)
	{
		Q_UNUSED(first)

		parsingSecondLine(almanach_.get(), second);
		parsingThirdLine(almanach_.get(), third);
	}
}
