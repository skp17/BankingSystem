#include "Date.h"
#include <iostream>
#include <ctime>

using namespace std;

Date::Date(uint day, uint month, uint year) 
    : m_day(day), m_month(month), m_year(year) {}

Date::Date(const Date &date)
    : m_day(date.m_day), m_month(date.m_month), m_year(date.m_year) {}

Date::~Date() {}

Date &Date::setDate(uint day, uint month, uint year) {
    // Get current year
    time_t now = time(0);
    struct tm *t = localtime(&now);
    uint current_year = t->tm_year + 1900;

    bool isValid = true;
    if (day < 1 || day > 31) {
		isValid = false;
		cerr << "day must be 1-31\n";
	} else if (month < 1 || month > 12) {
		isValid = false;
		cerr << "month must be 1-12\n";
	} else if (year < 1900 || year > current_year) {
		isValid = false;
		cerr << "year must be between 1900 and current year\n";
	}

	if ((month == 4 || month == 6 || month == 9 || month == 11)
		&& day == 31) {
        isValid = false;
    } else if ((month == 2) && (year % 4 == 0) && day > 29) {
        isValid = false;
    } else if ((month == 2) && (year % 4 != 0) && day > 28) {
        isValid = false;
    }

	if (isValid) {
        m_day = day; m_month = month; m_year = year;}
    else
		cerr << "Invalid Date\n";

    return *this;
}

uint Date::getDay() const {
    return m_day;
}

uint Date::getMonth() const {
    return m_month;
}

uint Date::getYear() const {
    return m_year;
}

void Date::printDate() const {
    cout << m_day << "/" << m_month << "/" << m_year << endl;
}