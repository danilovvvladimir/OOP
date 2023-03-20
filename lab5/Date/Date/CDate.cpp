#include "CDate.h"



CDate::CDate(Days day, Month month, Year year)
	: m_days(ConvertDateToDays(day, month, year))
{
}

CDate::CDate(Days timestamp)
	: m_days(timestamp)
{
}

Days CDate::GetDay() const
{
	return ConvertDaysToDateValues(m_days).day;
}

Month CDate::GetMonth() const
{
	return ConvertDaysToDateValues(m_days).month;
}

unsigned CDate::GetYear() const
{
	return ConvertDaysToDateValues(m_days).year;
}

WeekDay CDate::GetWeekDay() const
{
	switch (m_days % 7)
	{
	case 0:
		return WeekDay::THURSDAY;
	case 1:
		return WeekDay::FRIDAY;
	case 2:
		return WeekDay::SATURDAY;
	case 3:
		return WeekDay::SUNDAY;
	case 4:
		return WeekDay::MONDAY;
	case 5:
		return WeekDay::TUESDAY;
	default:
		return WeekDay::WEDNESDAY;
	}
}

bool CDate::IsValid() const
{
	if (m_days > MAX_AVAILABLE_DAY)
	{
		return false;
	}
	return true;
}

bool CDate::IsLeapYear(Year year) const
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

Days CDate::ConvertDateToDays(Days day, Month month, Year year) const
{
	Year yearGap = year - MIN_AVAILABLE_YEAR;
	Days daysInYearGap = yearGap * 365 + yearGap / 4 - yearGap / 100 + yearGap / 400;

	if (IsLeapYear(year - 1))
	{
		daysInYearGap++;
	}

	return daysInYearGap + MONTHS_OFFSET[IsLeapYear(year)][static_cast<Days>(month) - 1] + (day - 1);
}

DateValues CDate::ConvertDaysToDateValues(Days days) const
{
	Year year = (MIN_AVAILABLE_YEAR + 4 * days / (365 * 4 + 1)) + 1;

	int daysGap = (days - ConvertDateToDays(1, Month::JANUARY, year) + 1);
	if (daysGap <= 0)
	{
		year--;
		if (IsLeapYear(year))
		{
			daysGap += 366;
		}
		else
		{
			daysGap += 365;
		}
	}

	int monthIndex;
	Days d;

	for (monthIndex = 0; monthIndex < 12 && daysGap > MONTHS_OFFSET[IsLeapYear(year)][monthIndex]; monthIndex++)
	{
		d = daysGap - MONTHS_OFFSET[IsLeapYear(year)][monthIndex];
	}

	return { d, static_cast<Month>(monthIndex), year };
}
