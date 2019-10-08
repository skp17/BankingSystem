#include "Date.h"
#include "Person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

void save(string filename, const Person &p) {
    ofstream ofs(filename.c_str());
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(p);
}

void load(string filename, Person &p) {
    ifstream ifs(filename.c_str());
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(p);
}


using namespace std;

int main() {
    try {
        string filename = "person.xml";
        Person p1;

        ifstream ifs(filename.c_str());
        assert(ifs.good());
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(p1);
        p1.printPersonInfo();

    }
    catch( const exception &e ) {
        cerr << e.what() << endl;
    }


    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp loadPerson.cpp -o loadPerson /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall