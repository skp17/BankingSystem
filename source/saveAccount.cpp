#include <iostream>
#include <fstream>
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "ChequingAccount.h"
BOOST_CLASS_EXPORT(ChequingAccount)
#include "SavingsAccount.h"
BOOST_CLASS_EXPORT(SavingsAccount)


using namespace std;

int main() {
    try {
        string filename = "account.xml";
        Date dateOfBirth(9, 10, 1940);
        Person p1("John", "Lennon", dateOfBirth, 123456789);
        p1.setAddress("9 St-Catherine Est").setTelephone("514-777-7777");
        p1.setEmail("jlennon@gmail.com");

        Account *cheq = new ChequingAccount();
        cheq->deposit(500.25);

        Account *sav = new SavingsAccount();
        sav->deposit(700.50);

        ofstream ofs(filename.c_str());
        assert(ofs.good());
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(p1);
        oa << BOOST_SERIALIZATION_NVP(cheq);
        oa << BOOST_SERIALIZATION_NVP(sav);

    }
    catch( const exception &e ) {
        cerr << e.what() << endl;
    }


    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp saveAccount.cpp -o saveAccount /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall