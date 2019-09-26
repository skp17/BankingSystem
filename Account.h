#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <ctime>    /* struct tm */
#include "Date.h"
#include "Person.h"
using uint = unsigned int;


class Account {
    private:
        static uint count;
        uint accNum;
        const Person *accOwner;
        struct tm *dateCreated;
        double balance;

        virtual void setAccNum();

    public:
        Account(const Person&);
        Account(const Account&);
        virtual ~Account();

        //virtual string getAccOwner() const;
        uint getAccNum() const;
        void deposit(double);
        bool withdraw(double);
        virtual bool deleteAccount();
        string getDateCreated() const;
        virtual void print() const = 0;
};

#endif