#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include "BankManager.h"

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;

BankManager::BankManager() 
    : bankName("Bank Personel"), filename("bank.xml") 
{
    cout << "Welcome to " << bankName << endl;
}

BankManager::BankManager(const BankManager &BM)
    : bankName("Bank Personel"), filename("bank.xml")
{
    clients.assign( BM.clients.begin(), BM.clients.end() );
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
    return clients.size();
}

void BankManager::print() {
    cout << "# of registered clients: " << clients.size() << "\n\n";

    for(vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
        (*it)->printClientInfo();
}

void BankManager::saveArchive() {
    ofstream ofs(filename.c_str());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(*this);
}
bool BankManager::loadArchive() {
    bool result = false;
    ifstream ifs(filename.c_str());
    if ( ifs.is_open() ) {
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(*this);
        result = true;
    }
    return result;
}
