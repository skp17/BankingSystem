#include <iostream>
#include <string>
#include <ctime>    /* time_t, struct tm */
#include "Date.h"
#include "Person.h"
#include "Account.h"

using namespace std;

Account::Account()
{
    time_t now = time(0); // Returns number of seconds since 1970.
    dateCreated = localtime(&now);
    balance = 0;
}

Account::Account(const Account &acc)
    : accNum(acc.accNum), accountTypeNumber(acc.accountTypeNumber)
{
    balance = acc.balance;
    dateCreated = new struct tm;
    *dateCreated = *acc.dateCreated;
}

Account &Account::operator=(const Account &acc) {
    accNum = acc.accNum;
    accountTypeNumber = acc.accountTypeNumber;
    *dateCreated = *acc.dateCreated;
    balance = acc.balance;
}

Account::~Account() {
    delete dateCreated;
}

uint Account::getAccNum() const {
    return accNum;
}

void Account::setAccTypeNum(uint num) {
    accountTypeNumber = num;
}

uint Account::getAccTypeNum() const {
    return accountTypeNumber;
}

uint Account::getBalance() const {
    return balance;
}

void Account::deposit(double amount) {
    if (amount > 0)
        balance += amount;
    else
        throw invalid_argument( "Cannot deposit negative value" );
}

bool Account::withdraw(double amount) {
    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    else {
        return false;
    }
}

bool Account::deleteAccount() {
    if (balance > 0) {
        delete dateCreated;
        return true;
    }
    else {
        return false;
    }
}

struct tm Account::getDateCreated() const {
    struct tm tmp = *dateCreated;
    return tmp;
}





      