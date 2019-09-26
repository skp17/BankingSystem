#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include "Date.h"
#include "Person.h"
#include "Account.h"
//#include "SavingsAccount.h"
//#include "ChequingAccount.h"

enum accountType {Chequing, Savings};

class Client: public Person {
    private:
        uint accessNumber;
        uint PIN;               // user's pin 
        vector<Account *> chequingAccounts;
        vector<Account *> savingsAccounts;
        static uint count;      // Keeps track of no. of clients
        void setAccessNum();

    public:
        Client(const string &firstName, const string &lastName, 
            const Date &dayeOfBirth, uint SSN, uint pin);
        Client(const Client&);
        Client& operator=(const Client&);
        ~Client();

        bool createAccount(int);
        bool validateLogin(uint accessNumber, uint pin);
        void setPIN();
        uint getAccessNum() const;
        uint getNumOfAccounts() const;
        void print() const;

};


#endif // CLIENT_H