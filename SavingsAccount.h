#ifndef SavingsACCOUNT_H
#define SavingsACCOUNT_H

#include "Account.h"

class SavingsAccount: public Account {
    private:
        static uint savingsCount;  // no. of chequing accounts created
        virtual void setAccNum();
    public:
        SavingsAccount();
        SavingsAccount(const SavingsAccount&);
        SavingsAccount& operator=(const SavingsAccount&);
        virtual ~SavingsAccount();

        virtual void print() const;
};

#endif /* SavingsACCOUNT_H */