#ifndef PERSON_H
#define PERSON_H

#include "Date.h"
#include <string>
#include <boost/serialization/string.hpp>

using namespace std;
using namespace boost::archive;
using uint = unsigned int;

class Person {
    private:
        Date dateOfBirth;
        uint SSN; // Social Security Number
        string firstName, lastName;
        uint age;
        string address, telephone, email;
        void setAge();

        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive & ar, const uint version /* file_version */) {
            // Version is always the latest when saving
            ar & dateOfBirth;
            ar & SSN ;
            ar & age;
            ar & firstName;
            ar & lastName;
            ar & address;
            ar & telephone;
            ar & email;
        }
        template<class Archive>
        void load(Archive & ar, const uint version) {
            ar & dateOfBirth;
            ar & SSN ;
            ar & age;
            ar & firstName;
            ar & lastName;
            ar & address;
            ar & telephone;
            ar & email;

            // Add new data members here in future version
            // if(version > 0)
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        Person();
        Person(const string &firstname, const string &lastname, 
            const Date &dateOfBirth, uint SSN);
        Person(const string &, const string &, uint day, 
            uint month, uint year, uint);
        Person(const Person&);
        virtual ~Person();

        // set functions
        Person &setDateofBirth(const Date&);
        Person &setSSN(uint);
        Person &setName(const string&, const string&);
        Person &setAddress(const string&);
        Person &setTelephone(const string&);
        Person &setEmail(const string&);

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
        uint getSSN() const;

        virtual void printPersonInfo() const;
};

BOOST_CLASS_VERSION(Person, 0)

#endif /* PERSON_H */