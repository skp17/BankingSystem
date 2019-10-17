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
        Person p;
        Account *cheq = NULL;
        Account *sav = NULL;

        ifstream ifs(filename.c_str());
        assert(ifs.good());
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(p);
        ia >> BOOST_SERIALIZATION_NVP(cheq);
        ia >> BOOST_SERIALIZATION_NVP(sav);

        p.printPersonInfo();
        cheq->print();
        sav->print();

    }
    catch( const exception &e ) {
        cerr << e.what() << endl;
    }


    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp loadAccount.cpp -o loadAccount /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall