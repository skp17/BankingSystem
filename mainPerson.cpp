#include "Date.h"
#include "Person.h"
#include <iostream>
#include <fstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

using namespace std;
using boost::serialization::make_binary_object;
using boost::serialization::binary_object;

void save(const Person &p) {
    ofstream ofs("person.dat", ofstream::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa & make_binary_object((Person*)&p, sizeof(Person));
}

void load() {
    Person *p2 = new Person;
    ifstream ifs("person.dat", ifstream::binary | ifstream::in);
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia & make_binary_object(p2, sizeof(Person));
    p2->printPersonInfo();
}

int main() {

    try {
        Date dateOfBirth(9, 10, 1940);
        Person p1("John", "Lennon", dateOfBirth, 123456789);
        p1.setAddress("9 St-Catherine Est").setTelephone("514-777-7777");
        p1.setEmail("jlennon@gmail.com");

        save(p1);
        load();
    }
    catch( const exception &e) {
        cerr << e.what() << endl;
    }


    return 0;
}