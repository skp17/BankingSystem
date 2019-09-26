#include <iostream>
#include <string>
#include <ctime>    /* time_t, struct tm */
#include "Date.h"
#include "Person.h"
#include "Account.h"

using namespace std;

uint Account::count = 0;

Account::Account()
{
    ++count;
    time_t now = time(0); // Returns number of seconds since 1970.
    dateCreated = localtime(&now);
    balance = 0;
}

Account::Account(const Account &acc)
    : accNum(acc.accNum), dateCreated(acc.dateCreated)
{
    balance = acc.balance;
}

Account::~Account() {
    dateCreated = NULL;
}

void Account::setAccNum() {
    int accType = 101000;
    accNum = accType + count;
}

uint Account::getAccNum() const {
    return accNum;
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
        dateCreated = NULL;
        return true;
    }
    else {
        return false;
    }
}

string Account::getDateCreated() const {
    time_t t = mktime(dateCreated);
    return ctime(&t);
}

void Account::print() const {
    cout << "Account number: " << accNum << endl;
    cout << "  Balance " << balance << endl;
}




      