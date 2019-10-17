#include <iostream>
#include <string>
#include <ctime>    /* time_t, struct tm */
#include <iomanip>  /* setprecision */
#include "Account.h"
#include "ChequingAccount.h"

using namespace std;

uint ChequingAccount::chequingCount = 0;

ChequingAccount::ChequingAccount(): Account() {
    chequingCount++;
    accountTypeNumber = 101; // This number is for chequing accounts
    setAccNum();
}

ChequingAccount::ChequingAccount(const ChequingAccount &ca) 
    : Account(ca) { chequingCount++; }

ChequingAccount &ChequingAccount::operator=(const ChequingAccount &ca) {
    accNum = ca.accNum;
    accountTypeNumber = ca.accountTypeNumber;
    dateCreated = ca.dateCreated;
    balance = ca.balance;
    return *this;
}

ChequingAccount::~ChequingAccount() {}

void ChequingAccount::setAccNum() {
    accNum = accountTypeNumber*1e3 + chequingCount;
}

uint ChequingAccount::getAccTypeNum() const {
    return accountTypeNumber;
}

void ChequingAccount::print() const {
    cout << "----Checking Account----\n";
    cout << "  Account number: " << accNum << endl;
    cout << "  Balance: $" << setprecision(2) << fixed 
        << balance << endl << endl;;
}