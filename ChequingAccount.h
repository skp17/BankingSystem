#ifndef CHEQUINGACCOUNT_H
#define CHEQUINGACCOUNT_H

#include "Account.h"

class ChequingAccount: public Account {
    private:
        static uint chequingCount;  // no. of chequing accounts created
        virtual void setAccNum();
    public:
        ChequingAccount();
        ChequingAccount(const ChequingAccount&);
        ChequingAccount& operator=(const ChequingAccount&);
        virtual ~ChequingAccount();

        virtual void print() const;
};

#endif /* CHEQUINGACCOUNT_H */