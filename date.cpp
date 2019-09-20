#include "date.h"
#include <iostream>

using namespace std;

Date::Date(uint d, uint m, uint y) {

    if (d >= 1 && d <= 31) 
        day = d;
    else
        cerr << "Invalid day entered!\n";
    if (m >= 1 && m <= 12) 
        month = m;
    else
        cerr << "Invalid month entered!\n";
    if (y >= 1900 && y <= 2100) 
        year = y;
    else
        cerr << "Invalid year entered!\n";

}

Date::Date(const Date &date) {
    day = date.day;
    month = date.month;
    year = date.year;
}

void Date::setDate(uint d, uint m, uint y) {

    if (d >= 1 && d <= 31) 
        day = d;
    else
        cerr << "Invalid day entered!\n";
    if (m >= 1 && m <= 12) 
        month = m;
    else
        cerr << "Invalid month entered!\n";
    if (y >= 1900 && y <= 2100) 
        year = y;
    else
        cerr << "Invalid year entered!\n";
}

Date &Date::setDay(uint d) {
    if (d >= 1 && d <= 31) 
        day = d;
    else
        cerr << "Invalid year entered!\n";

    return *this;
}

Date &Date::setMonth(uint m) {
    if (m >= 1 && m <= 12) 
        month = m;
    else
        cerr << "Invalid month entered!\n";

    return *this;
}

Date &Date::setYear(uint y) {
    if (y >= 1900 && y <= 2100) 
        year = y;
    else
        cerr << "Invalid year entered!\n";

    return *this;
}

uint Date::getDay() const {
    return day;
}

uint Date::getMonth() const {
    return month;
}

uint Date::getYear() const {
    return year;
}

void Date::printDate() const {
    cout << day << "/" << month << "/" << year << endl;
}