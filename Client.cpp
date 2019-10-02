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
    chequingAccounts = new ChequingAccount[1];
    savingsAccounts = new SavingsAccount[1];
    numOfChequingAcc = 1;
    numOfSavingsAcc = 1;
    setAccessNum();
}

Client::Client(const string &firstName, const string &lastName, 
    const Date &dateOfBirth, uint SSN, uint pin)
    : Person(firstName, lastName, dateOfBirth, SSN) 
{
    clientCount++;
    this->PIN = pin;
    setAccessNum();
    chequingAccounts = new ChequingAccount[1];
    savingsAccounts = new SavingsAccount[1];
    numOfChequingAcc = 1;
    numOfSavingsAcc = 1;
}

Client::Client(const Client &c)
    : Person( c.getFName(), c.getLName(), c.getBirthDay(),
      c.getBirthMonth(), c.getBirthYear(), c.getSSN() ),
      accessNumber(c.accessNumber), PIN(c.PIN),
      numOfChequingAcc(c.numOfChequingAcc),
      numOfSavingsAcc(c.numOfSavingsAcc),
      chequingAccountsSize(c.numOfChequingAcc),
      savingsAccountsSize(c.numOfSavingsAcc)
{
    setAddress(c.getAddress());
    setTelephone(c.getTelephone());
    setEmail(c.getEmail());
    
    chequingAccounts = new ChequingAccount[numOfChequingAcc];
    for (uint i = 0; i < numOfChequingAcc; i++)
        chequingAccounts[i] = c.chequingAccounts[i];

    savingsAccounts = new SavingsAccount[numOfSavingsAcc];
    for (uint i = 0; i < numOfSavingsAcc; i++)
        savingsAccounts[i] = c.savingsAccounts[i];
}

Client::~Client() {
   delete [] chequingAccounts;
   delete [] savingsAccounts;
}

void Client::setAccessNum() {
    // Client access number: 
    // clientID birthMonth birthDay
    accessNumber =  clientCount*1e4 + getBirthMonth()*1e2
        + getBirthDay();
}

Account* Client::getAccount(uint accNum) {

    // Search chequing accounts
    for (uint i = 0; i < numOfChequingAcc; i++) {
        if (chequingAccounts[i].getAccNum() == accNum) {
            return &chequingAccounts[i];
        }
    }

    // Search savings accounts
    for (uint i = 0; i < numOfSavingsAcc; i++) {
        if (savingsAccounts[i].getAccNum() == accNum) {
            return &savingsAccounts[i];
        }
    }

    // return NULL if not found
    return NULL;
}

uint Client::createAccount(accountType accType) { // Chequing = 0, Savings = 1
    uint newAccountNumber = 0;
    if(accType == accountType::Chequing) { // Create new Chequing account
        
        // Create temporary space to store accounts
        Account *tmp_arr = new ChequingAccount[numOfChequingAcc];
        for(uint i = 0; i < numOfChequingAcc; i++)
            tmp_arr[i] = chequingAccounts[i];

        // Allocate new space for new account
        delete [] chequingAccounts;
        chequingAccounts = new (nothrow) ChequingAccount[numOfChequingAcc + 1];
        
        // If new allocation fails, restore accounts from tmp_arr
        if (chequingAccounts == nullptr) {
            chequingAccounts = new ChequingAccount[numOfChequingAcc];
            for(uint i = 0; i < numOfChequingAcc; i++)
                chequingAccounts[i] = tmp_arr[i];
        }
        else { // Continue if allocation is succesful

            ChequingAccount cheqAcc; // Create new ChequingAccount
            uint i = 0;
            for (; i < numOfChequingAcc; i++) {
                chequingAccounts[i] = tmp_arr[i];
            }
            chequingAccounts[i] = cheqAcc;
            numOfChequingAcc++;
            newAccountNumber =  cheqAcc.getAccNum();
        }
        delete [] tmp_arr;
    }
        
    if (accType == accountType::Savings) { // Create new Savings account
        
        // Create temporary space to store accounts
        Account *tmp_arr = new SavingsAccount[numOfSavingsAcc];
        for(uint i = 0; i < numOfSavingsAcc; i++)
            tmp_arr[i] = savingsAccounts[i];

        // Allocate new space for new account
        delete [] savingsAccounts;
        savingsAccounts = new (nothrow) SavingsAccount[numOfSavingsAcc + 1];
        
        // If new allocation fails, restore accounts from tmp_arr
        if (savingsAccounts == nullptr) {
            savingsAccounts = new SavingsAccount[numOfSavingsAcc];
            for(uint i = 0; i < numOfSavingsAcc; i++)
                savingsAccounts[i] = tmp_arr[i];
        }
        else { // Continue if allocation is succesful

            SavingsAccount SavAcc; // Create new SavingsAccount
            uint i = 0;
            for (; i < numOfSavingsAcc; i++) {
                savingsAccounts[i] = tmp_arr[i];
            }
            savingsAccounts[i] = SavAcc;
            numOfSavingsAcc++;
            newAccountNumber =  SavAcc.getAccNum();
        }
        delete [] tmp_arr;
    }

    return newAccountNumber;
}

bool Client::validateLogin(uint accNum, uint pin) const {
    if(accessNumber == accNum && PIN == pin)
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
    return numOfChequingAcc;
}

uint Client::getNumOfSavAccounts() const {
    return numOfSavingsAcc;
}

double Client::getAccBalance(uint accountNum) {
    if( getAccount(accountNum) != NULL )
        return getAccount(accountNum)->getBalance();
    else
        return -1; // Return -1 if account does not exist
}

struct tm Client::getAccDateCreation(uint accountNum) {
    if( getAccount(accountNum) != NULL )
        return (getAccount(accountNum)->getDateCreated());
    else
        return tm{-1};
}

bool Client::depositToAccount(uint accountNum, double amount) {
    bool success = false;
    if( getAccount(accountNum) != NULL) {
        getAccount(accountNum)->deposit(amount);
        success = true;
    }
    else {
        cerr << "No account with account number " << accountNum << " exists.\n";
        success = false;
    }

    return success;
}

bool Client::withdrawFromAccount(uint accountNum, double amount) {
    bool success = false;
    if( getAccount(accountNum) != NULL) {
        success = getAccount(accountNum)->withdraw(amount);
    }
    else {
        cerr << "No account with account number " << accountNum << " exists.\n";
        success = false;
    }
    
    return success; 
}

bool Client::deleteAccount(uint accountNum) {
    bool success = false;
    if( getAccount(accountNum) != NULL ) {
        if( getAccount(accountNum)->getBalance() == 0 ) {
            if( getAccount(accountNum)->getAccTypeNum() == 101 ) {

                // Search for account inside chequing account array
                for (uint i = 0; i < numOfChequingAcc; i++) {
                    if (chequingAccounts[i].getAccNum() == accountNum) {
                        for(uint j = i; j < (numOfChequingAcc-1); j++) {
                            chequingAccounts[j] = chequingAccounts[j + 1];
                        }
                        success = true;
                        break;
                    }
                }
            }

            if( getAccount(accountNum)->getAccTypeNum() == 201 ) {
                // Search for account inside savings account array
                for (uint i = 0; i < numOfSavingsAcc; i++) {
                    if (savingsAccounts[i].getAccNum() == accountNum) {
                        for(uint j = i; j < (numOfSavingsAcc-1); j++) {
                            savingsAccounts[j] = savingsAccounts[j + 1];
                        }
                        success = true;
                        break;
                    }
                }
            }
        }
        else 
            cerr << "Please withdraw all funds inside account before deleting.\n";
    }
    else
        cerr << "No account with account number " << accountNum << " exists.\n";

    return success;
}

void Client::listsAccounts() const {
    for(uint i = 0; i < numOfChequingAcc; i++)
        chequingAccounts[i].print();

    for(uint i = 0; i < numOfSavingsAcc; i++)
        savingsAccounts[i].print();
}

void Client::print() const {
    Person::printPersonInfo();
    cout << endl;
    cout << "Banking profile:\n";
    cout << "  Access Number: " << accessNumber << endl;
    cout << "  Number of Chequing Accounts: " << numOfChequingAcc;
    cout << endl << endl;
    for(uint i = 0; i < numOfChequingAcc; i++)
        chequingAccounts[i].print();

    cout << "  Number of Savings Accounts: " << numOfSavingsAcc;
    cout << endl << endl;
    for(uint i = 0; i < numOfSavingsAcc; i++)
        savingsAccounts[i].print();
    cout << endl;
}