#ifndef PERSON_H
#define PERSON_H

class Person {
    private:
        const char *fname, *lname;
        unsigned int age;
        //const Date dateOfBirth;
        const double SSN;

    public:
        Person();
        Person(const char*, const char*, unsigned int, double);
        Person(const Person&);
        ~Person();

        // set functions

        // get functions
};


#endif