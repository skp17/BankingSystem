#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include "BankManager.h"

using namespace std;

BankManager::BankManager() 
    : bankName("Bank Personel"), filename("bank.dat") 
{
    
}

BankManager::BankManager(const BankManager &BM)
    : bankName("Bank Personel"), filename("bank.dat")
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
            cerr << "\nYou already have a file with our bank."
                << " Please login with you existing credentials.\n";
            result = false;
            break;
        }
    }

    if ( client->getAge() < 18 ) {
        cerr << "\nYou must be at least 18 years of age to open a bank account\n";
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
        if(result) {
            for(vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
                if ( (*it)->getAccessNum() == accessNumber ) {
                    clients.erase(it);
                    break;
                }
            }
        }
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
