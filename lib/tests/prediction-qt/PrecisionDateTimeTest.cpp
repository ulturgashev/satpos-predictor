#include <QDebug>

#include <gtest/gtest.h>

#include <PrecisionDateTime.h>

constexpr auto OFFSET = 0.012345678901234;

namespace
{
	/**
	 * @brief Структура даты и времени
	 */
	typedef struct {
		int YYYY;     /** @brief год */
		int MM;       /** @brief месяц */
		int DD;       /** @brief день */
		int hh;       /** @brief часы */
		int mm;       /** @brief минуты */
		double ss;    /** @brief секунды */
	} DateTime;

	double time_conv(DateTime T)
	{
		double dd = (T.YYYY-=2000) * 365;
		dd += ((int)T.YYYY - 1)/4 + (T.MM > 2 || (int)T.YYYY%4 > 0);
		if(T.MM > 1) dd += 31;
		if(T.MM > 2) dd += 28;
		if(T.MM > 3) dd += 31;
		if(T.MM > 4) dd += 30;
		if(T.MM > 5) dd += 31;
		if(T.MM > 6) dd += 30;
		if(T.MM > 7) dd += 31;
		if(T.MM > 8) dd += 31;
		if(T.MM > 9) dd += 30;
		if(T.MM > 10) dd += 31;
		if(T.MM > 11) dd += 30;
		dd += T.DD - 1;
		dd *= 86400;
		dd += T.hh*3600 + T.mm*60 + T.ss;
		return dd;
	}

	DateTime makeDateTime(const QDateTime &dateTime, double offset)
	{
		const QDate date = dateTime.date();
		const QTime time = dateTime.time();

		return DateTime{date.year(), date.month(), date.day(), time.hour(), time.minute(), static_cast<double>(time.second() + offset)};
	}
}

TEST(PrecisionDateTimeTest, GlonassTimeTest)
{
	const QDateTime currentDateTime = QDateTime::currentDateTime();

	const DateTime dateTime = makeDateTime(currentDateTime, OFFSET);
	const Core::PrecisionDateTime precisionDateTime(currentDateTime, OFFSET);

	// TODO: Fixed in the future
	// ASSERT_DOUBLE_EQ(time_conv(dateTime), precisionDateTime.glonassTime());
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
