#ifndef CLIENT_H
#define CLIENT_H

#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "ChequingAccount.h"

enum class accountType {Chequing, Savings};

class Client: public Person {
    private:
        uint accessNumber;          // user's banking access number 
        uint PIN;                   // user's pin 
        Account *chequingAccounts;  // Contains pointers to chequing accounts
        Account *savingsAccounts;   // Contains pointers to savings accounts
        uint numOfChequingAcc;      // no. of chequing accounts user has
        uint numOfSavingsAcc;       // no. of savings accounts user has
        uint chequingAccountsSize;  // Current size of chequingAccounts array
        uint savingsAccountsSize;   // Current size of savingsAccounts array
        void setAccessNum();
        static uint clientCount;    // Keep track of number of clients created

    public:
        Client();
        Client(const string &firstName, const string &lastName, 
            const Date &dayeOfBirth, uint SSN, uint pin);
        Client(const Client&);
        Client& operator=(const Client&);
        ~Client();

        Account* getCheqAccounts() const;
        Account* getSavAccounts() const;
        uint createAccount(accountType);
        bool validateLogin(uint accessNumber, uint pin) const;
        void setPIN(uint pin);
        uint getAccessNum() const;
        uint getNumOfCheqAccounts() const;
        uint getNumOfSavAccounts() const;
        void print() const;
};


#endif /* CLIENT_H */