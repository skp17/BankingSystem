#include "Date.h"
#include "Person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

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


using namespace std;

int main() {
    try {
        string filename = "person.dat";
        Person p1;
        Person p2;

        ifstream ifs(filename.c_str(), ios::binary);
        assert(ifs.good());
        boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
        ia >> p1;
        ia >> p2;
        
        p1.printPersonInfo();
        p2.printPersonInfo();

    }
    catch( const exception &e ) {
        cerr << e.what() << endl;
    }


    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp loadPerson.cpp -o loadPerson /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall