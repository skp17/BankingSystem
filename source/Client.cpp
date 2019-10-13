#include <iostream>
#include <string>
#include <ctime>
#include "Person.h"
#include "Client.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "ChequingAccount.h"

using namespace std;
using uint = unsigned int;

uint Client::clientCount = 0;

Client::Client() {
    clientCount++;
    setAccessNum();
}

Client::Client(const string firstName, const string lastName, 
    const Date dateOfBirth, uint SSN, uint pin,
    string address, string telephone, string email)
    : Person(firstName, lastName, dateOfBirth, SSN, address, telephone, email) 
{
    clientCount++;
    this->PIN = pin;
    setAccessNum();
}

Client::Client(const Client &c)
    : Person( c.getFName(), c.getLName(), c.getBirthDay(),
      c.getBirthMonth(), c.getBirthYear(), c.getSSN(),
      c.getAddress(), c.getTelephone(), c.getEmail() ),
      accessNumber(c.accessNumber), PIN(c.PIN)
{   
    clientCount++;
    setAge();
    chequingAccounts.assign(c.chequingAccounts.begin(), c.chequingAccounts.end());
    savingsAccounts.assign(c.savingsAccounts.begin(), c.savingsAccounts.end());
}

Client &Client::operator=(const Client & c) {
    firstName = c.firstName;
    lastName = c.lastName;
    dateOfBirth = c.dateOfBirth;
    age = c.age;
    SSN = c.SSN;
    address = c.address;
    telephone = c.telephone;
    email = c.email;
    accessNumber = c.accessNumber;
    PIN = c.PIN;

    chequingAccounts.clear();
    savingsAccounts.clear();
    chequingAccounts.assign(c.chequingAccounts.begin(), c.chequingAccounts.end());
    savingsAccounts.assign(c.savingsAccounts.begin(), c.savingsAccounts.end());

    return *this;
}

Client::~Client() {
    chequingAccounts.clear();
    savingsAccounts.clear();
}

void Client::setAccessNum() {
    // Client access number: 
    // clientID birthMonth birthDay
    accessNumber =  clientCount*1e4 + getBirthMonth()*1e2
        + getBirthDay();
}

Account* Client::getAccount(uint accNum) {

    // Search chequing accounts
    for (vector<Account*>::iterator it = chequingAccounts.begin(); 
        it != chequingAccounts.end(); ++it) 
    {
        if ( (*it)->getAccNum() == accNum ) {
            return *it;
        }
    }

    // Search savings accounts
    for (vector<Account*>::iterator it = savingsAccounts.begin(); 
        it != savingsAccounts.end(); ++it) 
    {
        if ( (*it)->getAccNum() == accNum) {
            return *it;
        }
    }

    // return NULL if not found
    return NULL;
}

uint Client::createAccount(accountType accType) { // Chequing = 0, Savings = 1
    uint newAccountNumber = 0;
    vector<Account*>::iterator it;
    if(accType == accountType::Chequing) { // Create new Chequing account
        chequingAccounts.push_back( new ChequingAccount );
        newAccountNumber = chequingAccounts.back()->getAccNum();
    }
        
    if (accType == accountType::Savings) { // Create new Savings account
        savingsAccounts.push_back( new SavingsAccount );
        newAccountNumber = savingsAccounts.back()->getAccNum();
    }

    return newAccountNumber;
}

bool Client::validateLogin(uint accessNum, uint pin) const {
    if(accessNumber == accessNum && PIN == pin)
        return true;
    else 
        return false;
}

void Client::setPIN(uint pin) {
    PIN = pin;
}

uint Client::getAccessNum() const {
    return accessNumber;
}

uint Client::getNumOfCheqAccounts() const {
    return chequingAccounts.size();
}

uint Client::getNumOfSavAccounts() const {
    return savingsAccounts.size();
}

double Client::getAccBalance(uint accountNum) {
    if( getAccount(accountNum) != NULL )
        return getAccount(accountNum)->getBalance();
    else
        return -1; // Return -1 if account does not exist
}

Date Client::getAccDateCreation(uint accountNum) {
    if( getAccount(accountNum) != NULL )
        return (getAccount(accountNum)->getDateCreated());
    else
        cerr << "No account with account number " << accountNum << " exists.\n";
}

bool Client::depositToAccount(uint accountNum, double amount) {
    bool success = false;
    if( amount > 0 ) {
        if( getAccount(accountNum) != NULL) {
            getAccount(accountNum)->deposit(amount);
            success = true;
        }
        else {
            cerr << "No account with account number " << accountNum << " exists.\n";
            success = false;
        }
    }
    else
        cerr << "Please enter a postive amount\n";

    return success;
}

bool Client::withdrawFromAccount(uint accountNum, double amount) {
    bool success = false;
    if( amount > 0 ) {
        if( getAccount(accountNum) != NULL) {
            success = getAccount(accountNum)->withdraw(amount);
        }
        else {
            cerr << "No account with account number " << accountNum << " exists.\n";
            success = false;
        }
    }
    else
        cerr << "Please enter a postive amount\n";
    
    return success; 
}

bool Client::deleteAccount(uint accountNum) {
    bool result = false;
    // Check if account exist
    if( getAccount(accountNum) != NULL ) {
        // Check if account is empty
        if( getAccount(accountNum)->getBalance() == 0 ) {

            // Check if account is a chequing account
            if( getAccount(accountNum)->getAccTypeNum() == 101 ) { 

                // Search for account inside chequing account array
                for (vector<Account*>::iterator it = chequingAccounts.begin();
                    it != chequingAccounts.end(); ++it) 
                {   // Remove account from vector
                    if( (*it)->getAccNum() == accountNum ) {
                        chequingAccounts.erase(it);
                        result = true;
                        break;
                    }
                }
            }

            // Check if account is a savings account
            if( getAccount(accountNum)->getAccTypeNum() == 201 ) {
                // Search for account inside savings account array
                for (vector<Account*>::iterator it = savingsAccounts.begin();
                    it != savingsAccounts.end(); ++it) 
                {   // if found, relocate all the elements after the erased segment
                    if ( (*it)->getAccNum() == accountNum ) {
                        savingsAccounts.erase(it);
                        result = true;
                        break;
                    }
                }
            }
        }
        else 
            cerr << "Please withdraw all funds inside account " << accountNum
                << " before deleting.\n";
    }
    else
        cerr << "No account with account number " << accountNum << " exists.\n";

    return result;
}

bool Client::deleteAllAccounts() {
    bool ready_to_delete;
    bool allDeleted = true;

    // delete all chequing accounts if empty
    for(vector<Account*>::iterator it = chequingAccounts.begin(); it != chequingAccounts.end(); ) {
        ready_to_delete = deleteAccount( (*it)->getAccNum() ); // Return true if account is ready to be deleted
        if (ready_to_delete == true)
            it = chequingAccounts.erase(it);
        else {
            allDeleted = false;
            ++it;
        }
    }

    // delete all savings accounts if empty
    for(vector<Account*>::iterator it = savingsAccounts.begin(); it != savingsAccounts.end(); ) {
        ready_to_delete = deleteAccount( (*it)->getAccNum() ); // Return true if account is ready to be deleted
        if (ready_to_delete == true)
            it = savingsAccounts.erase(it);
        else {
            ++it;
            allDeleted = false;
        }
    }

    return allDeleted;
}

void Client::printAccount(uint accountNumber) {
    if( getAccount(accountNumber) != NULL )
        getAccount(accountNumber)->print();
    else
        cerr << "No account with account number " << accountNumber << " exists.\n";
}

void Client::listAccounts() {
    cout << "Banking profile:\n";
    cout << "  Access Number: " << accessNumber << endl;
    cout << "  Number of Chequing Accounts: " << getNumOfCheqAccounts();
    cout << endl << endl;
    for(vector<Account*>::iterator it = chequingAccounts.begin(); it != chequingAccounts.end(); ++it)
        (*it)->print();

    cout << "  Number of Savings Accounts: " << getNumOfSavAccounts();
    cout << endl << endl;
    for(vector<Account*>::iterator it = savingsAccounts.begin(); it != savingsAccounts.end(); ++it)
        (*it)->print();
    cout << endl;
}

void Client::printClientInfo() {
    Person::printPersonInfo();
    cout << endl;
    listAccounts();
}