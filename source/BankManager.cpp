#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include "BankManager.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;
using boost::serialization::make_binary_object;

BankManager::BankManager() 
    : bankName("Bank Personel"), filename("bank.dat") 
{
    cout << "Welcome to " << bankName << endl;
}

BankManager::~BankManager() {
    clients.clear();
    cout << "Good bye\n";
}

Client *BankManager::getClient(enum typeID ID, uint number) {

    if( ID == typeID::accessNumber ) {
        for(vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
            if ( (*it)->getAccessNum() == number )
                return *it;
        }
    }

    if( ID == typeID::SSN ) {
        for(vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
            if ( (*it)->getSSN() == number )
                return *it;
        }
    }

    return nullptr; /* return null_ptr is not found */
}

bool BankManager::addClient(Client *client) {
    bool result = false;
    // Determine if person already is registered with the bank
    for(vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if( client->getSSN() == (*it)->getSSN() ) {
            cerr << "You already have a file with our bank."
                << "Please login with you existing credentials.\n";
            result = false;
            break;
        }
    }

    if ( client->getAge() < 18 ) {
        cerr << "You must be at least 18 years of age to open a bank account\n";
        result = false;
    }
    else {
        clients.push_back(new Client(*client));
        nClients++;
        result = true;
    }

    return result;
}

bool BankManager::removeClient(uint accessNumber) {
    bool result = false;
    if( getClient(typeID::accessNumber, accessNumber) != nullptr ) {
        result = getClient(typeID::accessNumber, accessNumber)->deleteAllAccounts();
    }
    else
        cerr << "Invalid access number";

    return result;
}

string BankManager::getBankName() const {
    return bankName;
}

string BankManager::getfilename() const {
    return filename;
}

uint BankManager::getNumOfClients() const {
    return nClients;
}

void BankManager::print() const {

}

void BankManager::saveArchive() {
    ofstream ofs(filename.c_str(), ofstream::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << make_binary_object((BankManager*)this, sizeof(BankManager));
}

bool BankManager::loadArchive() {
    bool result = false;
    ifstream ifs(filename.c_str(), ifstream::binary);
    if ( ifs.is_open() ) {
        boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
        ia >> make_binary_object((BankManager*)this, sizeof(BankManager));
        result = true;
    }

    return result;
}



