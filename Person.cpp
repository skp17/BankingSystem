#include <iostream>
#include <string>
#include <ctime>
#include "Person.h"
#include "Date.h"

using namespace std;
using uint = unsigned int;

Person::Person(const string &fname, const string &lname, 
    const Date &birthDate, uint ssn)
    : dateOfBirth(birthDate), SSN(ssn)
{
    setName(fname, lname);
    setAddress("").setTelephone("").setEmail("");
    setAge();
}

Person::Person(const string &fname, const string &lname, uint day, 
    uint month, uint year, uint ssn) 
    : dateOfBirth(day, month, year), SSN(ssn) 
{
    setName(fname, lname);
    setAddress("").setTelephone("").setEmail("");
    setAge();
}

Person::Person(const Person &p)
    : dateOfBirth(p.dateOfBirth), age(p.age), SSN(p.SSN),
      firstName(p.firstName), lastName(p.lastName), 
      address(p.address), telephone(p.telephone),
      email(p.email) {}

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

Person &Person::setAddress(string add) {
    address = add;
    return *this;
}

Person &Person::setTelephone(string tel) {
    telephone = tel;
    return *this;
}

Person &Person::setEmail(string e) {
    email = e;
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

string Person::getTelephone() const {
    return telephone;
}

string Person::getEmail() const {
    return email;
}

string Person::getAddress() const {
    return address;
}

const uint Person::getSSN() const {
    return SSN;
}

void Person::printPersonInfo() const {
    cout << lastName << ", " << firstName << endl;
    cout << "  Birthday: ";
    dateOfBirth.printDate();
}