#include <iostream>
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
    nClients = 0;
    //cout << "Welcome to " << bankName << endl;
}

BankManager::BankManager(const BankManager &BM)
    : bankName(BM.bankName), filename(BM.filename) 
{
    nClients = BM.nClients;
    clients = new Client[BM.nClients];
    for( uint i = 0; i < BM.nClients; i++)
        clients[i] = BM.clients[i];
}

BankManager &BankManager::operator=(const BankManager &BM) {
    
    delete [] clients;
    clients = new Client[BM.nClients];
    for( uint i = 0; i < nClients; i++)
        clients[i] = BM.clients[i];

    return *this;
}

BankManager::~BankManager() {
    if (nClients > 0)
        delete [] clients;
    cout << "Good bye\n";
}

Client *BankManager::getClient(enum typeID ID, uint number) {

    if( ID == typeID::accessNumber ) {
        for(uint i = 0; i < nClients; i++) {
            if ( clients[i].getAccessNum() == number )
                return (clients + i);
        }
    }

    if( ID == typeID::SSN ) {
        for(uint i = 0; i < nClients; i++) {
            if ( clients[i].getSSN() == number )
                return (clients + i);
        }
    }

    return nullptr; // return null if not found

}

bool BankManager::addClient(Client &client) {
    bool result = false;
    // Determine if person already is registered with the bank
    for(uint i = 0 ; i < nClients; i++) {
        if( clients[i].getSSN() == client.getSSN() ) {
            cerr << "You already have a file with our bank."
                << "Please login with you existing credentials.\n";
            result = false;
            break;
        }
    }

    if ( client.getAge() < 18 ) {
        cerr << "You must be at least 18 years of age to open a bank account\n";
        result = false;
    }
    else {
        if(nClients > 1) {
            Client *tmp = new Client[nClients];
            for(uint i = 0; i < nClients; i++)
                tmp[i] = clients[i];
            
            delete [] clients;
            Client *clients = new (nothrow) Client[nClients + 1];
            
            // If new allocation fails, restore accounts from tmp_arr
            if( clients == nullptr ) {
                clients = new Client[nClients];
                for(uint i = 0; i < nClients; i++)
                    clients[i] = tmp[i];
            }
            else {
                uint i = 0;
                for(; i < nClients; i++)
                    clients[i] = tmp[i];

            clients[i] = client;
            }
        }
        else {
            clients = new Client[1];
            clients[0] = client;
        }
        nClients++;

        result = true;
    }

    return result;
}

bool BankManager::removeClient(uint accessNumber) {
    bool allAccountsEmpty = false;
    if( getClient(typeID::accessNumber, accessNumber) != nullptr) {
        allAccountsEmpty = getClient(typeID::accessNumber, accessNumber)->deleteAllAccounts();
        if (allAccountsEmpty) {
            for(uint i = 0; i < nClients; i++) {
                if( clients[i].getAccessNum() == accessNumber ) {
                    for(uint j = i; j < (nClients-1); j++) {
                        clients[j] = clients[j+1];
                    }
                    break;
                }
            }
        }
    else
        cerr << "Please withdraw all funds from accounts.\n";
    }   

    return allAccountsEmpty;
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
    cout << "Number of registered clients: " << nClients;
    cout << endl;
    for(uint i = 0; i < nClients; i++)
        clients[i].printClientInfo();

}
/*
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
*/



