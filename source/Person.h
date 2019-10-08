#ifndef PERSON_H
#define PERSON_H

#include "Date.h"
#include <string>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

using namespace std;
using namespace boost::archive;
using uint = unsigned int;

class Person {
    protected:
        Date dateOfBirth;
        uint SSN; // Social Security Number
        string firstName, lastName;
        uint age;
        string address, telephone, email;
        void setAge();

        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive &ar, const uint version /* file_version */) const {
            // Version is always the latest when saving
            ar & BOOST_SERIALIZATION_NVP(dateOfBirth);
            ar & BOOST_SERIALIZATION_NVP(SSN) ;
            ar & BOOST_SERIALIZATION_NVP(age);
            ar & BOOST_SERIALIZATION_NVP(firstName);
            ar & BOOST_SERIALIZATION_NVP(lastName);
            ar & BOOST_SERIALIZATION_NVP(address);
            ar & BOOST_SERIALIZATION_NVP(telephone);
            ar & BOOST_SERIALIZATION_NVP(email);
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            ar & BOOST_SERIALIZATION_NVP(dateOfBirth);
            ar & BOOST_SERIALIZATION_NVP(SSN) ;
            ar & BOOST_SERIALIZATION_NVP(age);
            ar & BOOST_SERIALIZATION_NVP(firstName);
            ar & BOOST_SERIALIZATION_NVP(lastName);
            ar & BOOST_SERIALIZATION_NVP(address);
            ar & BOOST_SERIALIZATION_NVP(telephone);
            ar & BOOST_SERIALIZATION_NVP(email);

            // Add new data members here in future version
            // if(version > 0)
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        Person();
        Person(const string &firstname, const string &lastname, 
            const Date &dateOfBirth, uint SSN,
            string address = "", string telephone = "", string email = "");
        Person(const string &firstname, const string &lastname, 
            uint day, uint month, uint year, uint SSN,
            string address = "", string telephone = "", string email = "");
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
        Date getBirthDate() const;
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