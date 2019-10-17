#include "Date.h"
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;

int main() {

    Date new_date;

    // open archive
    ifstream ifs("date.dat", ios::binary);
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);

    // restore date from the archive
    ia >> new_date;

    new_date.printDate();

    ifs.close();

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp loadDate.cpp -o loadDate /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall