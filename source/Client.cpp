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
    numOfChequingAcc = 0;
    numOfSavingsAcc = 0;
    chequingAccountsSize = 0;
    savingsAccountsSize = 0;
    setAccessNum();
}

Client::Client(const string &firstName, const string &lastName, 
    const Date &dateOfBirth, uint SSN, uint pin,
    string address, string telephone, string email)
    : Person(firstName, lastName, dateOfBirth, SSN, address, telephone, email) 
{
    clientCount++;
    this->PIN = pin;
    setAccessNum();
    numOfChequingAcc = 0;
    numOfSavingsAcc = 0;
    chequingAccountsSize = 0;
    savingsAccountsSize = 0;
}

Client::Client(const Client &c)
    : Person( c.getFName(), c.getLName(), c.getBirthDay(),
      c.getBirthMonth(), c.getBirthYear(), c.getSSN(),
      c.getAddress(), c.getTelephone(), c.getEmail() ),
      accessNumber(c.accessNumber), PIN(c.PIN),
      numOfChequingAcc(c.numOfChequingAcc),
      numOfSavingsAcc(c.numOfSavingsAcc),
      chequingAccountsSize(c.numOfChequingAcc),
      savingsAccountsSize(c.numOfSavingsAcc)
{   
    clientCount++;
    setAge();
    chequingAccounts = new ChequingAccount[numOfChequingAcc];
    for (uint i = 0; i < numOfChequingAcc; i++)
        chequingAccounts[i] = c.chequingAccounts[i];

    savingsAccounts = new SavingsAccount[numOfSavingsAcc];
    for (uint i = 0; i < numOfSavingsAcc; i++)
        savingsAccounts[i] = c.savingsAccounts[i];
}

Client &Client::operator=(const Client & client) {
    firstName = client.firstName;
    lastName = client.lastName;
    dateOfBirth = client.dateOfBirth;
    age = client.age;
    SSN = client.SSN;
    address = client.address;
    telephone = client.telephone;
    email = client.email;
    accessNumber = client.accessNumber;
    PIN = client.PIN;
    numOfChequingAcc = client.numOfChequingAcc;
    numOfSavingsAcc = client.numOfSavingsAcc;
    chequingAccountsSize = client.numOfChequingAcc;
    savingsAccountsSize = client.numOfSavingsAcc;

    if(numOfChequingAcc > 0)
        delete [] chequingAccounts;
    chequingAccounts = new ChequingAccount[numOfChequingAcc];
    for (uint i = 0; i < numOfChequingAcc; i++)
        chequingAccounts[i] = client.chequingAccounts[i];

    if(numOfSavingsAcc > 0)
        delete [] savingsAccounts;
    savingsAccounts = new SavingsAccount[numOfSavingsAcc];
    for (uint i = 0; i < numOfSavingsAcc; i++)
        savingsAccounts[i] = client.savingsAccounts[i];
    
    return *this;
}

Client::~Client() {
    if(numOfChequingAcc > 0)
        delete [] chequingAccounts;
    if(numOfSavingsAcc > 0)
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
        if( numOfChequingAcc > 0)
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
        if(numOfSavingsAcc > 0)
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

Date Client::getAccDateCreation(uint accountNum) {
    if( getAccount(accountNum) != NULL )
        return (getAccount(accountNum)->getDateCreated());
    else
        cerr << "No account with account number " << accountNum << " exists.\n";
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
    bool result = false;
    // Check if account exist
    if( getAccount(accountNum) != NULL ) {
        // Check if account is empty
        if( getAccount(accountNum)->getBalance() == 0 ) {
            // Check if account is a chequing account
            if( getAccount(accountNum)->getAccTypeNum() == 101 ) { 

                // Search for account inside chequing account array
                for (uint i = 0; i < numOfChequingAcc; i++) {
                    // if found, relocate all the elements after the erased segment
                    if (chequingAccounts[i].getAccNum() == accountNum) {
                        for(uint j = i; j < (numOfChequingAcc-1); j++) {
                            chequingAccounts[j] = chequingAccounts[j + 1];
                        }
                        result = true;
                        break;
                    }
                }
            }
            // Check if account is a chequing account
            if( getAccount(accountNum)->getAccTypeNum() == 201 ) {
                // Search for account inside savings account array
                for (uint i = 0; i < numOfSavingsAcc; i++) {
                    // if found, relocate all the elements after the erased segment
                    if (savingsAccounts[i].getAccNum() == accountNum) {
                        for(uint j = i; j < (numOfSavingsAcc-1); j++) {
                            savingsAccounts[j] = savingsAccounts[j + 1];
                        }
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
    bool result = true;

    // delete all chequing accounts if empty
    for(uint i = 0; (i < numOfChequingAcc) && result; i++) {
        result = deleteAccount( chequingAccounts[i].getAccNum() );
        if (result == false)
            break;
    }

    // delete all savings accounts if empty
    for(uint i = 0; (i < numOfSavingsAcc) && result; i++) {
        result = deleteAccount( savingsAccounts[i].getAccNum() );
        if (result == false)
            break;
    }

    return result;
}

void Client::listsAccounts() const {
    for(uint i = 0; i < numOfChequingAcc; i++)
        chequingAccounts[i].print();

    for(uint i = 0; i < numOfSavingsAcc; i++)
        savingsAccounts[i].print();
}

void Client::printClientInfo() const {
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