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
    chequingAccounts = new ChequingAccount();
    numOfChequingAcc++;
    setAccessNum();
}

Client::Client(const string &firstName, const string &lastName, 
    const Date &dateOfBirth, uint SSN, uint pin)
    : Person(firstName, lastName, dateOfBirth, SSN) 
{
    clientCount++;
    this->PIN = pin;
    setAccessNum();
    chequingAccounts = new ChequingAccount[1]();
    numOfChequingAcc++;
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
    if(numOfChequingAcc != 0) {
        if(numOfChequingAcc == 1)
            delete chequingAccounts;
        else if(numOfChequingAcc > 1)
            delete [] chequingAccounts;
    }

    if(numOfSavingsAcc != 0) {
        if(numOfSavingsAcc == 1)
            delete savingsAccounts;
        else if(numOfSavingsAcc > 1)
            delete [] savingsAccounts;
    }
}

void Client::setAccessNum() {
    // Client access number: 
    // clientID birthMonth birthDay
    accessNumber =  clientCount*1e4 + getBirthMonth()*1e2
        + getBirthDay();
}

Account* Client::getAccount(uint accNum) {
    Account* account = NULL;
    bool found = false;

    // Search chequing accounts
    for (uint i = 0; (i < numOfChequingAcc) || !found; i++) {
        if (chequingAccounts[i].getAccNum() == accNum) {
            account = &chequingAccounts[i];
            found = true;
        }
    }

    // Search savings accounts
    for (uint i = 0; (i < numOfSavingsAcc) || !found; i++) {
        if (savingsAccounts[i].getAccNum() == accNum) {
            account = &savingsAccounts[i];
            found = true;
        }
    }

    return account;
}

uint Client::createAccount(accountType accType) { // Chequing = 0, Savings = 1
    uint newAccountNumber = 0;
    if(accType == accountType::Chequing) { // Create new Chequing account
        
        Account *tmp_arr = chequingAccounts;
        chequingAccounts = new ChequingAccount[numOfChequingAcc + 1];
        ChequingAccount cheqAcc; // Create new ChequingAccount object
        uint i = 0;
        for (; i < numOfChequingAcc + 1; i++) {
            chequingAccounts[i] = tmp_arr[i];
        }
        chequingAccounts[++i] = cheqAcc;
        numOfChequingAcc++;
        delete [] tmp_arr;
        newAccountNumber =  cheqAcc.getAccNum();
    }
        
    if (accType == accountType::Savings) { // Create new Savings account
        Account *tmp_arr = savingsAccounts;
        savingsAccounts = new SavingsAccount[numOfSavingsAcc + 1];
        SavingsAccount cheqAcc; // Create new SavingsAccount object
        uint i = 0;
        for (; i < numOfSavingsAcc + 1; i++) {
            savingsAccounts[i] = tmp_arr[i];
        }
        savingsAccounts[++i] = cheqAcc;
        numOfSavingsAcc++;
        delete [] tmp_arr;
        newAccountNumber =  cheqAcc.getAccNum();
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

/*
Account *Client::getCheqAccounts() const {
    return chequingAccounts;
}

Account *Client::getSavAccounts() const {
    return savingsAccounts;
}
*/

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

void Client::listsAccounts() const {

}

void Client::print() const {
    Person::printPersonInfo();
    cout << endl;
    cout << "Banking profile:\n";
    cout << "  Access Number: " << accessNumber << endl;
    cout << "  Number of Chequing Accounts: " << numOfChequingAcc;
    cout << endl;
    cout << "  Number of Savings Accounts: " << numOfSavingsAcc;
    cout << endl;
}