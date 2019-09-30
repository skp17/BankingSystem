#include <iostream>
#include <string>
#include <ctime>    /* time_t, struct tm */
#include "Account.h"

using namespace std;

Account::Account()
{
    time_t now = time(0); // Returns number of seconds since 1970.
    dateCreated = *( localtime(&now) );
    balance = 0;
}

Account::Account(const Account &acc)
    : accNum(acc.accNum), accountTypeNumber(acc.accountTypeNumber)
{
    balance = acc.balance;
    dateCreated = acc.dateCreated;
}

Account &Account::operator=(const Account &acc) {
    accNum = acc.accNum;
    accountTypeNumber = acc.accountTypeNumber;
    dateCreated = acc.dateCreated;
    balance = acc.balance;
    return *this;
}

Account::~Account() {}

uint Account::getAccNum() const {
    return accNum;
}

void Account::setAccTypeNum(uint num) {
    accountTypeNumber = num;
}

uint Account::getAccTypeNum() const {
    return accountTypeNumber;
}

double Account::getBalance() const {
    return balance;
}

void Account::deposit(double amount) {
    if (amount >= 0)
        balance += amount;
    else
        throw invalid_argument( "Cannot deposit negative value" );
}

bool Account::withdraw(double amount) {
    bool success = false;
    if (amount <= balance) {
        balance -= amount;
        success = true;
    }
    else {
        success = false;
        throw invalid_argument( "Insufficient funds" );
    }

    return success;
}

bool Account::deleteAccount() { // Needs modifying
    if (balance == 0) {
        return true;
    }
    else {
        return false;
    }
}

struct tm Account::getDateCreated() const {
    return dateCreated;
}

void Account::setAccNum() {
    accountTypeNumber = 999;
    accNum = accountTypeNumber*1e3;
}


      