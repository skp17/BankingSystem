#ifndef CLIENT_H
#define CLIENT_H

#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "ChequingAccount.h"
#include <ctime>
#include <vector>
#include <string>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp>

using namespace boost::archive;
using namespace std;

enum class accountType {Chequing, Savings};

class Client: public Person {
    private:
        uint accessNumber;          // user's banking access number 
        string PIN;                 // user's pin 
        vector<Account*> chequingAccounts;  // Contains pointers to chequing accounts
        vector<Account*> savingsAccounts;   // Contains pointers to savings accounts
        static uint clientCount;    // Keep track of number of clients created

        Account* getAccount(uint accountNumber);  // Get account
        void setAccessNum();

        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive &ar, const uint version) const {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Person);
            ar.register_type(static_cast<ChequingAccount *>(NULL));
            ar.register_type(static_cast<SavingsAccount *>(NULL));
            ar & BOOST_SERIALIZATION_NVP(accessNumber);
            ar & BOOST_SERIALIZATION_NVP(PIN);
            ar & BOOST_SERIALIZATION_NVP(chequingAccounts);
            ar & BOOST_SERIALIZATION_NVP(savingsAccounts);
            ar & BOOST_SERIALIZATION_NVP(clientCount);
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Person);
            ar.register_type(static_cast<ChequingAccount *>(NULL));
            ar.register_type(static_cast<SavingsAccount *>(NULL));
            ar & BOOST_SERIALIZATION_NVP(accessNumber);
            ar & BOOST_SERIALIZATION_NVP(PIN);
            ar & BOOST_SERIALIZATION_NVP(chequingAccounts);
            ar & BOOST_SERIALIZATION_NVP(savingsAccounts);
            ar & BOOST_SERIALIZATION_NVP(clientCount);
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        Client();
        Client(const string firstName, const string lastName, 
            const Date dateOfBirth, uint SSN, string pin,
            string address = "", string telephone = "", string email = "");
        Client(const Client&);
        Client& operator=(const Client&);
        ~Client();

        uint createAccount(accountType);
        bool validateLogin(uint accessNumber, string pin) const;
        void setPIN(string pin);
        uint getAccessNum() const;
        uint getNumOfCheqAccounts() const;
        uint getNumOfSavAccounts() const;
        double getAccBalance(uint accountNumber);
        Date getAccDateCreation(uint accountNumber);
        bool depositToAccount(uint accountNumber, double amount);
        bool withdrawFromAccount(uint accountNumber, double amount);
        bool deleteAccount(uint accountNumber);
        bool deleteAllAccounts();
        void printAccount(uint accountNumber);
        void listAccounts();
        void printClientInfo();
};

BOOST_CLASS_VERSION(Client, 0)

#endif /* CLIENT_H */