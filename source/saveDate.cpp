#include "Date.h"
#include <iostream>
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;

int main() {

    Date orig_date(17, 12, 1992);

    // make an archive
    ofstream ofs("date.xml");
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(orig_date);
    ofs.close();

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp saveDate.cpp -o saveDate /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall