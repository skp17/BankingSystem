#include <iostream>
#include <string>
#include <ctime>
#include "Date.h"
#include "Person.h"
#include "Client.h"
#include "Account.h"

using namespace std;
using uint = unsigned int;

enum accountType {Chequing, Savings};

uint Client::count = 0;

Client::Client(const string &firstName, const string &lastName, 
    const Date &dateOfBirth, uint SSN, uint pin)
    : Person(firstName, lastName, dateOfBirth, SSN) 
{
    ++count;
    this->PIN = pin;
    setAccessNum();
    createAccount(Chequing);
}

Client::Client(const Client &c)
    : accessNumber(c.accessNumber), PIN(c.PIN),
      numOfChequingAcc(c.numOfChequingAcc),
      numOfSavingsAcc(c.numOfSavingsAcc),
      Person(c.getFName(), c.getLName(), c.getBirthDay(),
      c.getBirthMonth(), c.getBirthYear, c.getSSN()) 
{
    setAddress(c.getAddress());
    setTelephone(c.getTelephone());
    setEmail(c.getEmail());
    /*
    chequingAccounts = new CheckingAccounts[numOfChequingAcc];
    for (int i = 0; i < numOfChequingAcc; i++)
        chequingAccounts[i] = c.chequingAccounts[i];

        savingsAccounts = new savingsAccounts[numOfSavingsAcc];
    for (int i = 0; i < numOfSavingsAcc; i++)
        savingsAccounts[i] = c.savingsAccounts[i];

    */
     
     
}

bool Client::createAccount(int accType) { // Chequing = 0, Savings = 1
    bool result = false;
    if(accType == Chequing)
        // New Chequing account
        /*  
        Account *tmp_arr[numOfChequingAcc] = chequingAccounts;
        chequingAccounts = new CheckingAccounts[numOfChequingAcc + 1];
        ChequingAccount cheqAcc;
        int i = 0;
        for (; i < numOfChequingAcc + 1; i++) {
            chequingAccounts[i] = tmp_arr[i];
            }
        checkingAccounts[++i] = cheqAcc;
        delete [] tmp_arr;
        for (int i = 0; i < numOfChequingAcc; i++)
            tmp[i] = chequingAccounts[i];
        tmp[numofChequingAcc + 1] = 

        */
    if (accType == Savings)
        // New Savings account

    return result;
}