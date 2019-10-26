#define BOOST_TEST_MODULE BankManager test
#include <boost/test/unit_test.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <iostream>
#include <fstream>
#include "Date.h"
#include "Person.h"
#include "Client.h"
BOOST_CLASS_EXPORT(Client);
#include "Account.h"
#include "ChequingAccount.h"
BOOST_CLASS_EXPORT(ChequingAccount);
#include "SavingsAccount.h"
BOOST_CLASS_EXPORT(SavingsAccount);
#include "BankManager.h"


const string filename = "bank.dat";

void save(BankManager &manager)
{
    ofstream ofs(filename.c_str(), ios::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << manager;
}

bool load(BankManager &manager)
{
    bool result = false;
    ifstream ifs(filename.c_str(), ios::binary);
    if (ifs.is_open())
    {
        boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
        ia >> manager;
        result = true;
    }

    return result;
}

BOOST_AUTO_TEST_CASE( BankManager_test ) {
    BankManager BM;
    uint newAccountNum;

    BOOST_CHECK_EQUAL( BM.getBankName(), "Bank Personel");
    BOOST_CHECK_EQUAL( BM.getNumOfClients(), 0 );

    // Client 1
    Date dateOfBirth(9, 10, 1940);
    Client *client1 = new Client("John", "Lennon", dateOfBirth, 123456789, "4019");
    client1->setAddress("9 St-Catherine Est");
    client1->setTelephone("514-777-7777");
    client1->setEmail("jlennon@gmail.com");
    newAccountNum = client1->createAccount(accountType::Chequing);
    client1->depositToAccount(newAccountNum, 200.25);
    newAccountNum = client1->createAccount(accountType::Savings);
    client1->depositToAccount(newAccountNum, 500.00);
    newAccountNum = client1->createAccount(accountType::Savings);
    client1->depositToAccount(newAccountNum, 10000.00);

    BM.addClient(client1);
    BOOST_CHECK_EQUAL( BM.getNumOfClients(), 1 );

    // Client 2
    Date dateOfBirth2(1, 6, 1996);
    Client *client2 = new Client("Peter", "Parker", dateOfBirth2, 987654321, "9619");
    client2->setAddress("69th Road, Forest Hills");
    client2->setTelephone("917-777-7777");
    client2->setEmail("parker@gmail.com");
    newAccountNum = client2->createAccount(accountType::Chequing);
    client2->depositToAccount(newAccountNum, 75.50);

    BM.addClient(client2);
    BOOST_CHECK_EQUAL( BM.getNumOfClients(), 2 );

    // save bank information
    save(BM);

    client1->withdrawFromAccount(101001, 200.25);
    client1->withdrawFromAccount(201001, 500.00);
    client1->withdrawFromAccount(201002, 10000.00);
    BM.removeClient( client1->getAccessNum() );
    BOOST_CHECK_EQUAL( BM.getNumOfClients(), 1 );

    BM.removeClient( client2->getAccessNum() );
    BOOST_CHECK_EQUAL( BM.getNumOfClients(), 1 );

    delete client1;
    delete client2;
}

BOOST_AUTO_TEST_CASE( load_test ) {
    BankManager new_bm;
    load(new_bm);

    new_bm.print();
}