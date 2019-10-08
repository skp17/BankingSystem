#include "Date.h"
#include <iostream>
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;

int main() {

    Date new_date;

    // open archive
    ifstream ifs("date.xml");
    boost::archive::xml_iarchive ia(ifs);

    // restore date from the archive
    ia >> BOOST_SERIALIZATION_NVP(new_date);

    new_date.printDate();

    ifs.close();

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp loadDate.cpp -o loadDate /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall