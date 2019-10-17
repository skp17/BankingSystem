#include "Date.h"
#define BOOST_TEST_MODULE Date test
#include <boost/test/unit_test.hpp>
#include <iostream>

Date d1;

BOOST_AUTO_TEST_CASE(default_contructor__test)
{
    BOOST_CHECK(d1.getDay() == 1);
    BOOST_CHECK(d1.getMonth() == 1);
    BOOST_CHECK(d1.getYear() == 1970);
    d1.printDate();
}

BOOST_AUTO_TEST_CASE(setDate_test)
{

    d1.setDate(25, 12, 1999);

    BOOST_CHECK(d1.getDay() == 25);
    BOOST_CHECK(d1.getMonth() == 12);
    BOOST_CHECK(d1.getYear() == 1999);
    d1.printDate();
}

BOOST_AUTO_TEST_CASE(overloaded_contructor_test)
{
    try
    {
        Date d2(17, 12, 1992);

        BOOST_CHECK(d2.getDay() == 17);
        BOOST_CHECK(d2.getMonth() == 12);
        BOOST_CHECK(d2.getYear() == 1992);

        // Create invalid date
        Date d3(29, 2, 2019);
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << '\n';
    }
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
    Date d2(17, 12, 1992);
    Date d4 = d2;
    BOOST_CHECK(d4.getDay() == 17);
    BOOST_CHECK(d4.getMonth() == 12);
    BOOST_CHECK(d4.getYear() == 1992);
    d4.printDate();

    d1.setDate(19, 9, 2019);
    BOOST_CHECK(d1.getDay() == 19);
    BOOST_CHECK(d1.getMonth() == 9);
    BOOST_CHECK(d1.getYear() == 2019);
    d1.printDate();
}

// g++ -I /usr/local/boost_1_61_0/ -I ../source/ ../source/Date.cpp testDate.cpp -o testDate ../boost_serialization/libboost_serialization.a boost_test/libboost_unit_test_framework.a -std=c++11 -Wall
