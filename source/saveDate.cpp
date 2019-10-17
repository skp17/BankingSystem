#include "Date.h"
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;

int main() {

    Date orig_date(17, 12, 1992);

    // make an archive
    ofstream ofs("date.dat", ios::binary);
    assert(ofs.good());
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << orig_date;
    ofs.close();

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp saveDate.cpp -o saveDate /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall