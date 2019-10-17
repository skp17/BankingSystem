#ifndef CHEQUINGACCOUNT_H
#define CHEQUINGACCOUNT_H

#include "Account.h"
#include <boost/serialization/base_object.hpp>

class ChequingAccount: public Account {
    private:
        static uint chequingCount;  // no. of chequing accounts created
        virtual void setAccNum();

        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive &ar, const uint version) const {
            // save base class information
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Account);
            ar & BOOST_SERIALIZATION_NVP(chequingCount);
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            // load base class information
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Account);
            ar & BOOST_SERIALIZATION_NVP(chequingCount);
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        ChequingAccount();
        ChequingAccount(const ChequingAccount&);
        ChequingAccount& operator=(const ChequingAccount&);
        virtual ~ChequingAccount();

        virtual uint getAccTypeNum() const;
        virtual void print() const;
};

BOOST_CLASS_VERSION(ChequingAccount, 0)

#endif /* CHEQUINGACCOUNT_H */