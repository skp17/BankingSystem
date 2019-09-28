#include <iostream>
#include <string>
#include <ctime>    /* time_t, struct tm */
#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "ChequingAccount.h"

uint ChequingAccount::chequingCount = 0;

ChequingAccount::ChequingAccount(): Account() {
    chequingCount++;
    accountTypeNumber = 101;
    setAccNum();
}

ChequingAccount::ChequingAccount(const ChequingAccount &ca) 
    : Account(ca) { chequingCount++; }

ChequingAccount &ChequingAccount::operator=(const ChequingAccount &ca) {
    accNum = ca.accNum;
    accountTypeNumber = ca.accountTypeNumber;
    *dateCreated = *ca.dateCreated;
    balance = ca.balance;
}

ChequingAccount::~ChequingAccount() {}

void ChequingAccount::setAccNum() {
    accNum = accountTypeNumber*1e3 + chequingCount;
}

void ChequingAccount::print() const {
    cout << "----Checking Account----\n";
    cout << "  Account number: " << accNum << endl;
    cout << "  Balance: " << balance << endl;
}