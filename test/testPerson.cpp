
#include "catch.hpp"
#include "Date.h"
#include "Person.h"
#define BOOST_TEST_MODULE Person test
#include <boost/test/unit_test.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include <fstream>

const string filename = "person.dat";

BOOST_AUTO_TEST_CASE(Person_test)
{
    Person p1("John", "Lennon", 9, 10, 1940, 123456789);
    p1.setAddress("9 St-Catherine Est").setTelephone("514-777-7777");
    p1.setEmail("jlennon@gmail.com");

    BOOST_CHECK(p1.getFName() == "John");
    BOOST_CHECK(p1.getLName() == "Lennon");
    BOOST_CHECK(p1.getBirthDay() == 9);
    BOOST_CHECK(p1.getBirthMonth() == 10);
    BOOST_CHECK(p1.getBirthYear() == 1940);
    BOOST_CHECK(p1.getAge() == 79);
    BOOST_CHECK(p1.getSSN() == 123456789);
    BOOST_CHECK(p1.getAddress() == "9 St-Catherine Est");
    BOOST_CHECK(p1.getTelephone() == "514-777-7777");
    BOOST_CHECK(p1.getEmail() == "jlennon@gmail.com");

    // test operator=
    Person p2 = p1;
    BOOST_CHECK(p1.getFName() == "John");
    BOOST_CHECK(p1.getLName() == "Lennon");
    BOOST_CHECK(p1.getBirthDay() == 9);
    BOOST_CHECK(p1.getBirthMonth() == 10);
    BOOST_CHECK(p1.getBirthYear() == 1940);
    BOOST_CHECK(p1.getAge() == 79);
    BOOST_CHECK(p1.getSSN() == 123456789);

    // Change Person values
    Date birthdate(1, 11, 1961);
    Person someone("Reed", "Richards", birthdate, 123789456);

    BOOST_CHECK(someone.getFName() == "Reed");
    BOOST_CHECK(someone.getLName() == "Richards");
    BOOST_CHECK(someone.getAge() == 57);
    BOOST_CHECK(someone.getBirthDay() == 1);
    BOOST_CHECK(someone.getBirthMonth() == 11);
    BOOST_CHECK(someone.getBirthYear() == 1961);
    BOOST_CHECK(someone.getSSN() == 123789456);
    BOOST_CHECK(someone.getAddress() == "");
    BOOST_CHECK(someone.getTelephone() == "");
    BOOST_CHECK(someone.getEmail() == "");

    someone.setName("Michael", "Scott");
    Date newBirth(17, 12, 1992);
    someone.setDateofBirth(newBirth);

    BOOST_CHECK(someone.getFName() == "Michael");
    BOOST_CHECK(someone.getLName() == "Scott");
    BOOST_CHECK(someone.getBirthDay() == 17);
    BOOST_CHECK(someone.getBirthMonth() == 12);
    BOOST_CHECK(someone.getBirthYear() == 1992);
    BOOST_CHECK(someone.getAge() == 26);
}

BOOST_AUTO_TEST_CASE(save_test)
{
    Date dateOfBirth(9, 10, 1940);
    Person p1("John", "Lennon", dateOfBirth, 123456789);
    p1.setAddress("9 St-Catherine Est").setTelephone("514-777-7777");
    p1.setEmail("jlennon@gmail.com");

    Date dateOfBirth2(1, 5, 1996);
    Person p2("Peter", "Parker", dateOfBirth2, 987654321);
    p2.setAddress("69th Road, Forest Hills");
    p2.setTelephone("917-777-7777");
    p2.setEmail("parker@gmail.com");

    ofstream ofs(filename.c_str(), ios::binary);
    assert(ofs.good());
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << p1;
    oa << p2;
    ofs.close();
}

BOOST_AUTO_TEST_CASE(load_test)
{
    Person p1;
    Person p2;

    ifstream ifs(filename.c_str(), ios::binary);
    assert(ifs.good());
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia >> p1;
    ia >> p2;
    ifs.close();

    BOOST_CHECK(p1.getFName() == "John");
    BOOST_CHECK(p1.getLName() == "Lennon");
    BOOST_CHECK(p1.getAge() == 79);
    BOOST_CHECK(p1.getBirthDay() == 9);
    BOOST_CHECK(p1.getBirthMonth() == 10);
    BOOST_CHECK(p1.getBirthYear() == 1940);
    BOOST_CHECK(p1.getSSN() == 123456789);
    BOOST_CHECK(p1.getAddress() == "9 St-Catherine Est");
    BOOST_CHECK(p1.getTelephone() == "514-777-7777");
    BOOST_CHECK(p1.getEmail() == "jlennon@gmail.com");

    BOOST_CHECK(p2.getFName() == "Peter");
    BOOST_CHECK(p2.getLName() == "Parker");
    BOOST_CHECK(p2.getAge() == 23);
    BOOST_CHECK(p2.getBirthDay() == 1);
    BOOST_CHECK(p2.getBirthMonth() == 5);
    BOOST_CHECK(p2.getBirthYear() == 1996);
    BOOST_CHECK(p2.getSSN() == 987654321);
    BOOST_CHECK(p2.getAddress() == "69th Road, Forest Hills");
    BOOST_CHECK(p2.getTelephone() == "917-777-7777");
    BOOST_CHECK(p2.getEmail() == "parker@gmail.com");
}

// g++ -I /usr/local/boost_1_61_0/ -I ../source/ ../source/Date.cpp ../source/Person.cpp testPerson.cpp -o testPerson ../boost_serialization/libboost_serialization.a boost_test/libboost_unit_test_framework.a -std=c++11 -Wall