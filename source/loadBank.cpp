#include <iostream>
#include <fstream>
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "ChequingAccount.h"
BOOST_CLASS_EXPORT(ChequingAccount)
#include "SavingsAccount.h"
BOOST_CLASS_EXPORT(SavingsAccount)
#include "Client.h"
BOOST_CLASS_EXPORT(Client)
#include "BankManager.h"

using namespace std;

const string filename = "bank.xml";

void saveArchive(BankManager &BM) {
    ofstream ofs(filename.c_str());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(BM);
}

void loadArchive(BankManager &BM) {
    ifstream ifs(filename.c_str());
    boost::archive::xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(BM);
}

int main() {
    BankManager BM;
    loadArchive(BM);
    BM.print();
    saveArchive(BM);

    return 0;
}