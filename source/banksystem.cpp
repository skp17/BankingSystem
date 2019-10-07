#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include "Client.h"
#include "BankManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <termios.h>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;
using boost::serialization::make_binary_object;

const string filename = "bank.dat";

void saveArchive(BankManager *BM) {
    cout << "Saving\n";
    ofstream ofs(filename.c_str(), ofstream::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << make_binary_object((BankManager*)BM, sizeof(BankManager));
}

bool loadArchive(BankManager *BM) {
    bool result = false;
    ifstream ifs(filename.c_str(), ifstream::binary);
    if ( ifs.is_open() ) {
        cout << "Loading\n";
        boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
        ia >> make_binary_object((BankManager*)BM, sizeof(BankManager));
        result = true;
    }

    return result;
}

int main() {

    try {
        
        BankManager *BM = new BankManager;
        loadArchive(BM);
        cout << "# of clients: " << BM->getNumOfClients() << endl;
/*
        Date dateOfBirth(9, 10,1940);
        Client *newClient = new Client("John", "Lennon", dateOfBirth, 123456789, 4019);
        newClient->setAddress("9 St-Catherine Est");
        newClient->setTelephone("514-777-7777");
        newClient->setEmail("jlennon@gmail.com");
        newClient->setPIN(1111);
        BM->addClient(newClient);
        
        cout << "# of clients: " << BM->getNumOfClients() << endl;
        */
        saveArchive(BM);

    }
    catch( const exception &e ) {
        cerr << "Exception: "  << e.what() << "\n\n";
    }

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp Client.cpp BankManager.cpp banksystem.cpp -o banksystem /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall

