#include <iostream>
#include <string>
#include <ctime>    /* time_t, struct tm */
#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "SavingsAccount.h"

uint SavingsAccount::savingsCount = 0;

SavingsAccount::SavingsAccount(): Account() {
    savingsCount++;
    accountTypeNumber = 201;
    setAccNum();
}

SavingsAccount::SavingsAccount(const SavingsAccount &sa) 
    : Account(sa) { savingsCount++; }

SavingsAccount &SavingsAccount::operator=(const SavingsAccount &sa) {
    accNum = sa.accNum;
    accountTypeNumber = sa.accountTypeNumber;
    *dateCreated = *sa.dateCreated;
    balance = sa.balance;
}

SavingsAccount::~SavingsAccount() {}

void SavingsAccount::setAccNum() {
    accNum = accountTypeNumber*1e3 + savingsCount;
}

void SavingsAccount::print() const {
    cout << "----Savings Account----\n";
    cout << "  Account number: " << accNum << endl;
    cout << "  Balance: " << balance << endl;
}