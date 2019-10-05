#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include <iostream>
#include <fstream>
#include <string>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

using namespace std;
using boost::serialization::make_binary_object;

void save(Account *acc, string filename) {
    ofstream ofs(filename.c_str(), ofstream::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa & make_binary_object((Account*)acc, sizeof(Account));
}

void load(Account *acc, string filename) {
    ifstream ifs(filename.c_str(), ifstream::binary);
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia & make_binary_object((Account*)acc, sizeof(Account));
}

int main() {
    try {
        string filename = "account.dat";
        //shared_ptr<Account> account = make_shared<ChequingAccount>();
        Account* account = new ChequingAccount;
        account->deposit(500.25);

        // Before saving
        cout << "Information before saving\n";
        account->print();
        save(account, filename);

        Account* newAccount = new ChequingAccount;
        load(newAccount, filename);

        // After loading
        cout << "Information after loading\n";
        newAccount->print();
        uint year = newAccount->getDateCreated().getYear();
        uint month = newAccount->getDateCreated().getMonth();
        uint day = newAccount->getDateCreated().getDay();
        cout << "Account created on " << day << "/" << month << "/" << year << endl;

    }
    catch ( const exception &e ) {
        cerr << e.what() << endl;
    }

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp mainAccount.cpp -o mainAccount /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall