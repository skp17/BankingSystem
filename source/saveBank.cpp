#include <iostream>
#include <fstream>
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "ChequingAccount.h"
BOOST_CLASS_EXPORT(ChequingAccount)
#include "SavingsAccount.h"
BOOST_CLASS_EXPORT(SavingsAccount)
#include "Client.h"
BOOST_CLASS_EXPORT(Client)
#include "BankManager.h"

using namespace std;

int main() {

    string filename = "bank.xml";
    BankManager BM;
    uint newAccountNum;

    Date dateOfBirth(9, 10, 1940);
    Client *client1 = new Client("John", "Lennon", dateOfBirth, 123456789, "4019");
    client1->setAddress("9 St-Catherine Est");
    client1->setTelephone("514-777-7777");
    client1->setEmail("jlennon@gmail.com");
    newAccountNum = client1->createAccount(accountType::Chequing);
    client1->depositToAccount(newAccountNum, 200.25);
    newAccountNum = client1->createAccount(accountType::Savings);
    client1->depositToAccount(newAccountNum, 500.00);

    Date dateOfBirth2(1, 6, 1996);
    Client *client2 = new Client("Peter", "Parker", dateOfBirth2, 987654321, "9619");
    client2->setAddress("69th Road, Forest Hills");
    client2->setTelephone("917-777-7777");
    client2->setEmail("parker@gmail.com");
    newAccountNum = client2->createAccount(accountType::Chequing);
    client2->depositToAccount(newAccountNum, 75.50);


    BM.addClient(client1);
    BM.addClient(client2);
    BM.print();

    {
        ofstream ofs(filename.c_str());
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(BM);
    }
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp Client.cpp BankManager.cpp saveBank.cpp -o saveBank /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall