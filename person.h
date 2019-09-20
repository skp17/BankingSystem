#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include <string>

using namespace std;

class Person {
    private:
        string fname, lname;
        const Date dateOfBirth;
        unsigned int age;
        const unsigned int SSN;

    public:
        Person();
        Person(string, string, unsigned int,
            unsigned int, unsigned int, unsigned int);
        Person(const Person&);
        ~Person();

        // set functions
        void setFName(string);
        void setLName(string);
        void setBirthDate(unsigned int, unsigned int, unsigned int);
        void setBirthDate(const Date&);

        // get functions
        string getFName() const;
        string getLName() const;
        const Date* getBirthDate(const Date&) const;
        unsigned int getAge() const;
        const unsigned int getSSN() const;

        void printPersonInfo() const;
};


#endif