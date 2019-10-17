#ifndef SavingsACCOUNT_H
#define SavingsACCOUNT_H

#include "Account.h"
#include <boost/serialization/base_object.hpp>

class SavingsAccount: public Account {
    private:
        static uint savingsCount;  // no. of chequing accounts created
        virtual void setAccNum();

        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive &ar, const uint version) const {
            // save base class information
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Account);
            ar & BOOST_SERIALIZATION_NVP(savingsCount);
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            // load base class information
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Account);
            ar & BOOST_SERIALIZATION_NVP(savingsCount);
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        SavingsAccount();
        SavingsAccount(const SavingsAccount&);
        SavingsAccount& operator=(const SavingsAccount&);
        virtual ~SavingsAccount();

        virtual uint getAccTypeNum() const;
        virtual void print() const;
};

BOOST_CLASS_VERSION(SavingsAccount, 0)

#endif /* SavingsACCOUNT_H */