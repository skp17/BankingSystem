#ifndef BANKMANAGER_H
#define BANKMANAGER_H

#include "Client.h"
#include "Account.h"
#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
using namespace std;
using namespace boost::archive;
using uint = unsigned int;

enum class typeID {accessNumber, SSN};

class BankManager {
    private:
        const string bankName;  // Name of the bank
        const string filename;  // Name of file where data is stored
        Client* clients;        // Clients of the bank
        uint nClients;

        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive &ar, const uint version) {
            ar.register_type(static_cast<Client *>(NULL));
            ar & bankName;
            ar & filename;
            ar & nClients;
            ar & clients;
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            ar.register_type(static_cast<Client *>(NULL));
            ar & bankName;
            ar & filename;
            ar & nClients;
            ar & clients;
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        BankManager();
        BankManager(const BankManager&);
        BankManager& operator=(const BankManager&);
        ~BankManager();

        Client* getClient(enum typeID, uint number);
        bool addClient(Client&);
        bool removeClient(uint accessNumber);
        string getBankName() const;
        string getfilename() const;     // Returns name of file where data is stored
        uint getNumOfClients() const;
        void print() const;

        //void saveArchive();
        //bool loadArchive();
        //void backupArchive();
};

BOOST_CLASS_VERSION(BankManager, 0)

#endif /* BANKMANAGER_H */