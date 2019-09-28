#ifndef PERSON_H
#define PERSON_H

#include "Date.h"
#include <string>

using namespace std;
using uint = unsigned int;

class Person {
    private:
        const Date dateOfBirth;
        uint SSN; // Social Security Number
        string firstName, lastName;
        uint age;
        string address, telephone, email;
        void setAge();
    public:
        Person();
        Person(const string &firstname, const string &lastname, 
            const Date &dateOfBirth, uint SSN);
        Person(const string &, const string &, uint day, 
            uint month, uint year, uint);
        Person(const Person&);
        ~Person();

        // set functions
        Person &setDateofBirth(Date&);
        Person &setSSN(uint);
        Person &setName(const string&, const string&);
        Person &setAddress(string);
        Person &setTelephone(string);
        Person &setEmail(string);

        // get functions
        string getFName() const;
        string getLName() const;
        uint getBirthDay() const;
        uint getBirthMonth() const;
        uint getBirthYear() const;
        uint getAge() const;
        string getAddress() const;
        string getTelephone() const;
        string getEmail() const;
        const uint getSSN() const;

        virtual void printPersonInfo() const;
};

#endif