#ifndef PERSON_H
#define PERSON_H

#include "Date.h"
#include <string>

using namespace std;
using uint = unsigned int;

class Person {
    private:
        string firstName, lastName;
        const Date dateOfBirth;
        uint age;
        const uint SSN; // Social Security Number
        void setAge();

    public:
        Person(const string &, const string &, 
            const Date &, uint);
        Person(const string &, const string &, uint day, 
            uint month, uint year, uint);
        Person(const Person&);
        ~Person();

        // set function
        Person &setName(const string&, const string&);

        // get functions
        string getFName() const;
        string getLName() const;
        uint getBirthDay() const;
        uint getBirthMonth() const;
        uint getBirthYear() const;
        uint getAge() const;
        const uint getSSN() const;

        void printPersonInfo() const;
};

#endif