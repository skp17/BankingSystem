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

void load(Client *client, string filename) {
    ifstream ifs(filename.c_str(), ifstream::binary);
    boost::archive::xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(client);
}

int main() {
    try {
        string filename = "client.xml";
        uint newAccountNum;

        Date dateOfBirth2(1, 6, 1996);
        Client *client2 = new Client("Peter", "Parker", dateOfBirth2, 987654321, 9619);
        client2->setAddress("69th Road, Forest Hills");
        client2->setTelephone("917-777-7777");
        client2->setEmail("parker@gmail.com");
        client2->setPIN(6991);
        //newAccountNum = client2->createAccount(accountType::Chequing);
        //client2->depositToAccount(newAccountNum, 75.50);
        //client2->printClientInfo();

        // Client 1
        Date dateOfBirth(9, 10, 1940);
        Client *client1 = new Client("John", "Lennon", dateOfBirth, 123456789, 4019);
        client1->setAddress("9 St-Catherine Est");
        client1->setTelephone("514-777-7777");
        client1->setEmail("jlennon@gmail.com");
        client1->setPIN(1111);
        newAccountNum = client1->createAccount(accountType::Chequing);
        client1->depositToAccount(newAccountNum, 200.25);
        newAccountNum = client1->createAccount(accountType::Savings);
        client1->depositToAccount(newAccountNum, 500.00);
        //client1->printClientInfo();

        //save(client1, filename);
        ofstream ofs(filename.c_str());
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(client1);
        oa << BOOST_SERIALIZATION_NVP(client2);


    }
    catch ( const exception &e ) {
        cerr << e.what() << endl;
    }

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp Client.cpp saveClient.cpp -o saveClient /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall