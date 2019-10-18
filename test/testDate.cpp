#include "Date.h"
#define BOOST_TEST_MODULE Date test
#include <boost/test/unit_test.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include <fstream>

const string filename = "date.dat";

BOOST_AUTO_TEST_CASE( Date__test )
{
    Date d1;
    BOOST_CHECK(d1.getDay() == 1);
    BOOST_CHECK(d1.getMonth() == 1);
    BOOST_CHECK(d1.getYear() == 1970);
    d1.printDate();

    // Change date values
    d1.setDate(25, 12, 1999);
    BOOST_CHECK(d1.getDay() == 25);
    BOOST_CHECK(d1.getMonth() == 12);
    BOOST_CHECK(d1.getYear() == 1999);

    // test overloaded constructor
    Date d2(17, 12, 1992);
    BOOST_CHECK(d2.getDay() == 17);
    BOOST_CHECK(d2.getMonth() == 12);
    BOOST_CHECK(d2.getYear() == 1992);

    // Create invalid date
    Date d3(29, 2, 2019);

    // test operator=
    Date d4 = d2;
    BOOST_CHECK(d4.getDay() == 17);
    BOOST_CHECK(d4.getMonth() == 12);
    BOOST_CHECK(d4.getYear() == 1992);

}

BOOST_AUTO_TEST_CASE( save_test ) {
    Date orig_date(17, 12, 1992);

    // make an archive
    ofstream ofs(filename.c_str(), ios::binary);
    assert(ofs.good());
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << orig_date;
    ofs.close();
}

BOOST_AUTO_TEST_CASE( load_test ) {
    Date new_date;

    // open archive
    ifstream ifs(filename.c_str(), ios::binary);
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);

    // restore date from the archive
    ia >> new_date;
    BOOST_CHECK(new_date.getDay() == 17);
    BOOST_CHECK(new_date.getMonth() == 12);
    BOOST_CHECK(new_date.getYear() == 1992);
    new_date.printDate();

    ifs.close();
}

// g++ -I /usr/local/boost_1_61_0/ -I ../source/ ../source/Date.cpp testDate.cpp -o testDate ../boost_serialization/libboost_serialization.a boost_test/libboost_unit_test_framework.a -std=c++11 -Wall
