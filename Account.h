#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Date.h"
#include "Person.h"
using uint = unsigned int;


class Account {
    private:
        const uint accNum;
        Person *accOwner;
        const Date dateCreated;
        double amount;

    public:
        Account();
        Account(const Person &p);
        Account(const Account &acc);
        ~Account();

        virtual string getAccOwner() const = 0;
        virtual uint getAccNum() const = 0;
        virtual bool deposit(double) = 0;
        virtual bool withdraw(double) = 0;
        virtual bool deleteAccount() = 0;
        virtual void print() = 0;
};

#endif