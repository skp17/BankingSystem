#include <iostream>
#include <string>
#include <ctime>
#include "Person.h"
#include "Date.h"

using namespace std;
using uint = unsigned int;

Person::Person() {
    Date birth;
    setDateofBirth(birth).setSSN(0).setName("", "");
    setAddress("").setTelephone("").setEmail("");
}

Person::Person(const string &fname, const string &lname, 
    const Date &birthDate, uint ssn)
    : dateOfBirth(birthDate)
{
    setSSN(ssn);
    setName(fname, lname);
    setAddress("").setTelephone("").setEmail("");
    setAge();
}

Person::Person(const string &fname, const string &lname, uint day, 
    uint month, uint year, uint ssn) 
    : dateOfBirth(day, month, year)
{
    setSSN(ssn);
    setName(fname, lname);
    setAddress("").setTelephone("").setEmail("");
    setAge();
}

Person::Person(const Person &p)
    : dateOfBirth(p.dateOfBirth), SSN(p.SSN),
      firstName(p.firstName), lastName(p.lastName), age(p.age),
      address(p.address), telephone(p.telephone),
      email(p.email) {}

Person::~Person() {}

Person &Person::setDateofBirth(const Date &birth) {
    dateOfBirth = birth;
    setAge();
    return *this;
}

Person &Person::setSSN(uint ssn) {
    SSN = ssn;
    return *this;
}

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

Person &Person::setAddress(const string &add) {
    address = add;
    return *this;
}

Person &Person::setTelephone(const string &tel) {
    telephone = tel;
    return *this;
}

Person &Person::setEmail(const string &e) {
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
    cout << "  Birthday: "; dateOfBirth.printDate();
    cout << "  Age: " << age << endl;
    cout << "  Address: " << address << endl;
    cout << "  Telephone: " << telephone << endl;
    cout << "  Email: " << email << endl;
}