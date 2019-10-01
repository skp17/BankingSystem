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
        static uint clientCount;    // Keep track of number of clients created

        Account* getAccount(uint accountNumber);  // Get account
        void setAccessNum();

    public:
        Client();
        Client(const string &firstName, const string &lastName, 
            const Date &dateOfBirth, uint SSN, uint pin);
        Client(const Client&);
        Client& operator=(const Client&);
        ~Client();

        // Account* getCheqAccounts() const;    // Get all chequing accounts
        // Account* getSavAccounts() const;     // Get all savings accounts
        uint createAccount(accountType);// Needs modifying
        bool validateLogin(uint accessNumber, uint pin) const;
        void setPIN(uint pin);
        uint getAccessNum() const;
        uint getNumOfCheqAccounts() const;
        uint getNumOfSavAccounts() const;
        bool depositToAccount(uint accountNumber, double amount);
        bool withdrawFromAccount(uint accountNumber, double amount);
        bool deleteAccount(uint accessNumber);  // IMPLEMENT
        void listsAccounts() const;
        void print() const;
};


#endif /* CLIENT_H */