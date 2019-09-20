#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
    private:
        const unsigned int accNum;
        // Person *accOwner; // create class Person

    public:
        Account();
        Account(/* const Person p */);
        Account(const Account &acc);
        ~Account();

        virtual bool setAccOwner(/* const Person &p */) = 0;
        virtual void getAccOwner() const = 0;
        virtual void getAccNum() const = 0;
        virtual bool deleteAccount() = 0;
        virtual void print() = 0;
};

#endif