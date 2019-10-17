#include "Date.h"
#include "Person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

using namespace std;

void save(string filename, const Person &p) {
    ofstream ofs(filename.c_str(), ios::binary);
    assert(ofs.good());
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << p;
}

void load(string filename, Person &p) {
    ifstream ifs(filename.c_str(), ios::binary);
    assert(ifs.good());
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia >> p;
}

int main() {
    try {
        string filename = "person.dat";
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

    }
    catch( const exception &e ) {
        cerr << e.what() << endl;
    }


    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp savePerson.cpp -o savePerson /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall