#include <iostream>
#include <string>
#include <ctime>    /* time_t, struct tm */
#include <iomanip>  /* setprecision */
#include "Account.h"
#include "SavingsAccount.h"

using namespace std;

uint SavingsAccount::savingsCount = 0;

SavingsAccount::SavingsAccount(): Account() {
    savingsCount++;
    accountTypeNumber = 201; // This number is for savings
    setAccNum();
}

SavingsAccount::SavingsAccount(const SavingsAccount &sa) 
    : Account(sa) { savingsCount++; }

SavingsAccount &SavingsAccount::operator=(const SavingsAccount &sa) {
    accNum = sa.accNum;
    accountTypeNumber = sa.accountTypeNumber;
    dateCreated = sa.dateCreated;
    balance = sa.balance;
    return *this;
}

SavingsAccount::~SavingsAccount() {}

void SavingsAccount::setAccNum() {
    accNum = accountTypeNumber*1e3 + savingsCount;
}

void SavingsAccount::print() const {
    cout << "----Savings Account----\n";
    cout << "  Account number: " << accNum << endl;
    cout << "  Balance: $" << setprecision(2) << fixed
        << balance << endl << endl;
}