#ifndef BANKMANAGER_H
#define BANKMANAGER_H

#include "Client.h"
#include "Account.h"
#include <string>
#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
using namespace std;
using uint = unsigned int;

enum class typeID {accessNumber, SSN};

class BankManager {
    private:
        string bankName;            // Name of the bank
        string filename;            // Name of file where data is stored
        vector<Client*> clients;    // Clients of the bank

    public:
        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive &ar, const uint version) const {
            ar.register_type(static_cast<Client*>(NULL));
            ar & BOOST_SERIALIZATION_NVP(bankName);
            ar & BOOST_SERIALIZATION_NVP(filename);
            ar & BOOST_SERIALIZATION_NVP(clients);
        }
        template<class Archive>
        void load(Archive &ar, const uint version) {
            ar.register_type(static_cast<Client*>(NULL));
            ar & BOOST_SERIALIZATION_NVP(bankName);
            ar & BOOST_SERIALIZATION_NVP(filename);
            ar & BOOST_SERIALIZATION_NVP(clients);
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

        BankManager();
        BankManager(const BankManager&);
        ~BankManager();

        Client *getClient(enum typeID, uint number);
        bool addClient(Client*);
        bool removeClient(uint accessNumber); // FINISH IMPLEMENTING
        string getBankName() const;
        string getfilename() const;     // Returns name of file where data is stored
        uint getNumOfClients() const;
        void print();

        void saveArchive();
        bool loadArchive();
        //void backupArchive();
};

BOOST_CLASS_VERSION(BankManager, 0)

#endif /* BANKMANAGER_H */