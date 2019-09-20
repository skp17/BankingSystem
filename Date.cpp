#include "Date.h"
#include <iostream>

using namespace std;

Date::Date() {
    day = 1;
    month = 1;
    year = 1970;
}

Date::Date(unsigned int d, unsigned int m, unsigned int y) {

    if (d >= 1 && d <= 31) 
        day = d;
    else {
        cerr << "Invalid day entered!\n";
        d = 1;
    }
    if (m >= 1 && m <= 12) 
        month = m;
    else {
        cerr << "Invalid month entered!\n";
        m = 1;
    }
    if (y >= 1900 && y <= 2100) 
        year = y;
    else {
        cerr << "Invalid year entered!\n";
        year = 1970;
    }

}

Date::Date(const Date &date) {
    day = date.day;
    month = date.month;
    year = date.year;
}

Date::~Date() {

}

void Date::setDate(unsigned int d, unsigned int m, unsigned int y) {

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

void Date::setDay(unsigned int d) {
    if (d >= 1 && d <= 31) 
        day = d;
    else
        cerr << "Invalid year entered!\n";
}

void Date::setMonth(unsigned int m) {
    if (m >= 1 && m <= 12) 
        month = m;
    else
        cerr << "Invalid month entered!\n";
}

void Date::setYear(unsigned int y) {
    if (y >= 1900 && y <= 2100) 
        year = y;
    else
        cerr << "Invalid year entered!\n";
}

unsigned int Date::getDay() const {
    return day;
}

unsigned int Date::getMonth() const {
    return month;
}

unsigned int Date::getYear() const {
    return year;
}

void Date::printDate() const {
    cout << day << "/" << month << "/" << year << endl;
}