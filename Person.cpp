#include <iostream>
#include <string>
#include <ctime>
#include "Person.h"
#include "Date.h"

using namespace std;
using uint = unsigned int;

Person::Person(const string &firstName, const string &lastName, 
    const Date &birthDate, uint ssn)
    : dateOfBirth(birthDate), SSN(ssn)
{
    setName(firstName, lastName);
    setAge();
}

Person::Person(const string &firstname, const string &lastname, uint day, 
    uint month, uint year, uint ssn) 
    : dateOfBirth(day, month, year), SSN(ssn) 
{
    setName(firstName, lastName);
    setAge();
}

Person::Person(const Person &p)
    : dateOfBirth(p.dateOfBirth), age(p.age), SSN(p.SSN),
      firstName(p.firstName), lastName(p.lastName) {}

Person::~Person() {}

Person &Person::setName(const string &fname, const string &lname) {
    if (fname != "")
        firstName = fname;
    else
        throw invalid_argument( "must enter first name" );

    if (lname != "")
        lastName = lname;
    else
        throw invalid_argument( "must enter last name" );

    return *this;
}

string Person::getFName() const {
    return firstName; 
}

string Person::getLName() const {
    return lastName; 
}

uint Person::getBirthDay() const {
    return dateOfBirth.getDay();
}

uint Person::getBirthMonth() const {
    return dateOfBirth.getMonth();
}

uint Person::getBirthYear() const {
    return dateOfBirth.getYear();
}

void Person::setAge() {
    
    // Get current time
    time_t now = time(0);

    struct tm birth = {0};
    birth.tm_year = dateOfBirth.getYear() - 1900;
    birth.tm_mon = dateOfBirth.getMonth() - 1;
    birth.tm_mday = dateOfBirth.getDay();

    uint long delta_sec = difftime(now, mktime(&birth));
    age = delta_sec/86400/365.25;   // divided by seconds in a day 
                                    // and divided by days in a year.
}

uint Person::getAge() const {
    return age;
}

const uint Person::getSSN() const {
    return SSN;
}

void Person::printPersonInfo() const {
    cout << lastName << ", " << firstName << endl;
    cout << "  Birthday: ";
    dateOfBirth.printDate();
}