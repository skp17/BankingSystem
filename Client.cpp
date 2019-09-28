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

enum accountType {Chequing, Savings};

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
    chequingAccounts = new ChequingAccount();
    numOfChequingAcc++;
}

Client::Client(const Client &c)
    : accessNumber(c.accessNumber), PIN(c.PIN),
      numOfChequingAcc(c.numOfChequingAcc),
      numOfSavingsAcc(c.numOfSavingsAcc),
      chequingAccountsSize(c.numOfChequingAcc),
      savingsAccountsSize(c.numOfSavingsAcc),
      Person( c.getFName(), c.getLName(), c.getBirthDay(),
      c.getBirthMonth(), c.getBirthYear(), c.getSSN() ) 
{
    setAddress(c.getAddress());
    setTelephone(c.getTelephone());
    setEmail(c.getEmail());
    
    chequingAccounts = new ChequingAccount[numOfChequingAcc];
    for (int i = 0; i < numOfChequingAcc; i++)
        chequingAccounts[i] = c.chequingAccounts[i];

    savingsAccounts = new SavingsAccount[numOfSavingsAcc];
    for (int i = 0; i < numOfSavingsAcc; i++)
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

uint Client::createAccount(int accType) { // Chequing = 0, Savings = 1
    if(accType == Chequing) { // New Chequing account
        
        Account *tmp_arr = chequingAccounts;
        chequingAccounts = new ChequingAccount[numOfChequingAcc + 1];
        ChequingAccount cheqAcc; // Create new ChequingAccount object
        int i = 0;
        for (; i < numOfChequingAcc + 1; i++) {
            chequingAccounts[i] = tmp_arr[i];
        }
        chequingAccounts[++i] = cheqAcc;
        numOfChequingAcc++;
        delete [] tmp_arr;
        return cheqAcc.getAccNum();
    }
        
    if (accType == Savings) { // New Savings account
        Account *tmp_arr = savingsAccounts;
        savingsAccounts = new SavingsAccount[numOfSavingsAcc + 1];
        SavingsAccount cheqAcc; // Create new SavingsAccount object
        int i = 0;
        for (; i < numOfSavingsAcc + 1; i++) {
            savingsAccounts[i] = tmp_arr[i];
        }
        savingsAccounts[++i] = cheqAcc;
        numOfSavingsAcc++;
        delete [] tmp_arr;
        return cheqAcc.getAccNum();
    }
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

Account *Client::getCheqAccounts() const {
    return chequingAccounts;
}

Account *Client::getSavAccounts() const {
    return savingsAccounts;
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