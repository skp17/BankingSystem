#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <ctime>    /* struct tm */
#include "Date.h"
#include "Person.h"
using uint = unsigned int;


class Account {
    private:
        static uint count;      // Keeps track no of accounts
        uint accNum;            // Account number
        struct tm *dateCreated;
        double balance;

        virtual void setAccNum();

    public:
        Account();
        Account(const Account&);
        virtual ~Account();

        uint getAccNum() const;
        void deposit(double);
        bool withdraw(double);
        virtual bool deleteAccount();
        string getDateCreated() const;
        virtual void print() const = 0;
};

#endif // ACCOUNT_H