#include <iostream>
#include <string>
#include <ctime>    /* time_t, struct tm */
#include "Account.h"

using namespace std;

Account::Account()
{
    time_t now = time(0); // Returns number of seconds since 1970.
    struct tm *dt = localtime(&now);
    dateCreated.setDate(
        dt->tm_mday,
        (dt->tm_mon + 1),
        (dt->tm_year + 1900)
    );
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
        cerr << "Cannot deposit negative value\n";
}

bool Account::withdraw(double amount) {
    bool success = false;
    if (amount <= balance) {
        balance -= amount;
        success = true;
    }
    else {
        success = false;
        cerr << "Insufficient funds\n";
    }

    return success;
}

bool Account::deleteAccount() { // TODO Needs modifying
    if (balance == 0) {
        return true;
    }
    else {
        return false;
    }
}

Date Account::getDateCreated() const {
    return dateCreated;
}

void Account::setAccNum() { // TODO delete 999
    accountTypeNumber = 999;
    accNum = accountTypeNumber*1e3;
}


      