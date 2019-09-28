#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <ctime>    /* struct tm */
#include "Person.h"
using uint = unsigned int;


class Account {
    protected:
        uint accNum;            // Account number
        uint accountTypeNumber; // number that identifies account type
        struct tm *dateCreated;
        double balance;

        virtual void setAccNum() = 0;

    public:
        Account();
        Account(const Account&);
        Account& operator=(const Account&);
        virtual ~Account();

        uint getAccNum() const;
        void setAccTypeNum(uint);
        uint getAccTypeNum() const;
        uint getBalance() const;
        void deposit(double);
        bool withdraw(double);
        bool deleteAccount();
        struct tm getDateCreated() const;
        virtual void print() const = 0;
};

#endif // ACCOUNT_H