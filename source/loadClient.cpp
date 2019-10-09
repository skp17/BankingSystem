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
#include "Client.h"
BOOST_CLASS_EXPORT(Client)

using namespace std;

void save(Client *client, string filename) {
    ofstream ofs(filename.c_str(), ofstream::binary);
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(client);
}

// Notice client passed as reference and not as pointer
void load(Client &client, string filename) {
    ifstream ifs(filename.c_str(), ifstream::binary);
    boost::archive::xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(client);
}

int main() {
    try {

        string filename = "client.xml";
        Client *client = new Client();
        load(*client, filename);
        client->printClientInfo();

    }
    catch ( const exception &e ) {
        cerr << e.what() << endl;
    }

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp Client.cpp loadClient.cpp -o loadClient /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall