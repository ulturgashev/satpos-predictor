#pragma once

typedef struct {
	double YYYY;    /*!< @brief год */
	double MM;      /*!< @brief месяц */
	double DD;      /*!< @brief день */
	double hh;      /*!< @brief часы */
	double mm;      /*!< @brief минуты */
	double ss;      /*!< @brief секунды */
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
