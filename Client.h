#ifndef CLIENT_H
#define CLIENT_H

#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "ChequingAccount.h"
#include <ctime>
#include <boost/serialization/base_object.hpp>

enum class accountType {Chequing, Savings};

class Client: public Person {
    private:
        uint accessNumber;          // user's banking access number 
        uint PIN;                   // user's pin 
        Account *chequingAccounts;  // Contains pointers to chequing accounts
        Account *savingsAccounts;   // Contains pointers to savings accounts
        uint numOfChequingAcc;      // no. of chequing accounts user has
        uint numOfSavingsAcc;       // no. of savings accounts user has
        uint chequingAccountsSize;  // Current size of chequingAccounts array
        uint savingsAccountsSize;   // Current size of savingsAccounts array
        static uint clientCount;    // Keep track of number of clients created

        Account* getAccount(uint accountNumber);  // Get account
        void setAccessNum();

        template<class Archive>
        void save(Archive &ar, const uint version) {
            ar & boost::serialization::base_object<Person>(*this);
            ar.register_type(static_cast<ChequingAccount *>(NULL));
            ar.register_type(static_cast<SavingsAccount *>(NULL));
            ar & accessNumber;
            ar & PIN;
            ar & chequingAccounts;
            ar & savingsAccounts;
            ar & numOfChequingAcc;
            ar & numOfSavingsAcc;
            ar & chequingAccountsSize;
            ar & savingsAccountsSize;
            ar & clientCount;
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            ar & boost::serialization::base_object<Person>(*this);
            ar.register_type(static_cast<ChequingAccount *>(NULL));
            ar.register_type(static_cast<SavingsAccount *>(NULL));
            ar & accessNumber;
            ar & PIN;
            ar & chequingAccounts;
            ar & savingsAccounts;
            ar & numOfChequingAcc;
            ar & numOfSavingsAcc;
            ar & chequingAccountsSize;
            ar & savingsAccountsSize;
            ar & clientCount;
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        Client();
        Client(const string &firstName, const string &lastName, 
            const Date &dateOfBirth, uint SSN, uint pin);
        Client(const Client&);
        Client& operator=(const Client&);
        ~Client();

        uint createAccount(accountType);
        bool validateLogin(uint accessNumber, uint pin) const;
        void setPIN(uint pin);
        uint getAccessNum() const;
        uint getNumOfCheqAccounts() const;
        uint getNumOfSavAccounts() const;
        double getAccBalance(uint accountNumber);
        Date getAccDateCreation(uint accountNumber);
        bool depositToAccount(uint accountNumber, double amount);
        bool withdrawFromAccount(uint accountNumber, double amount);
        bool deleteAccount(uint accessNumber);
        void listsAccounts() const;
        void printClientInfo() const;
};

BOOST_CLASS_VERSION(Client, 0)

#endif /* CLIENT_H */