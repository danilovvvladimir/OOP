#pragma once

using Days = unsigned;
using Year = unsigned;

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

struct DateValues
{
	Days day;
	Month month;
	Year year;
};

const Days MAX_AVAILABLE_DAY = 2932532;

const Year MIN_AVAILABLE_YEAR = 1970;
const Year MAX_AVAILABLE_YEAR = 9999;

const int MONTHS_OFFSET[2][12] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 },
};

class CDate
{
public:
	CDate(Days day, Month month, Year year);
	CDate(Days timestamp = 0);

	Days GetDay() const;
	Month GetMonth() const;
	Year GetYear() const;
	WeekDay GetWeekDay() const;

	bool IsValid() const;
private:
	Days ConvertDateToDays(Days day, Month month, Year year) const;
	DateValues ConvertDaysToDateValues(Days days) const;
	bool IsLeapYear(Year year) const;
	Days m_days;
};

//	–езультат применени€ данных операций к недопустимой дате не измен€ет ее значени€.
//	ѕри выходе результата после выполнени€ операций за пределы диапазона 01 : 01 : 1970 Ц 31 : 12 : 9999 дата должна стать недопустимой.
