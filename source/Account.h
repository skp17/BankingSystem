#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Date.h"
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>

using uint = unsigned int;

class Account {
    protected:
        uint accNum;            // Account number
        uint accountTypeNumber; // number that identifies account type
        Date dateCreated;
        double balance;

        virtual void setAccNum() = 0;

        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive &ar, const uint version) const {
            ar & BOOST_SERIALIZATION_NVP(accNum);
            ar & BOOST_SERIALIZATION_NVP(accountTypeNumber);
            ar & BOOST_SERIALIZATION_NVP(dateCreated);
            ar & BOOST_SERIALIZATION_NVP(balance);
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            ar & BOOST_SERIALIZATION_NVP(accNum);
            ar & BOOST_SERIALIZATION_NVP(accountTypeNumber);
            ar & BOOST_SERIALIZATION_NVP(dateCreated);
            ar & BOOST_SERIALIZATION_NVP(balance);
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        Account();
        Account(const Account&);
        Account& operator=(const Account&);
        virtual ~Account();

        uint getAccNum() const;
        void setAccTypeNum(uint);
        uint getAccTypeNum() const;
        double getBalance() const;
        void deposit(double);
        bool withdraw(double);
        bool deleteAccount();
        Date getDateCreated() const;
        virtual void print() const = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Account)
BOOST_CLASS_VERSION(Account, 0)

#endif /* ACCOUNT_H */