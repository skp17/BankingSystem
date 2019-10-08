#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include "Client.h"
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

void save(Client *client, string filename) {
    ofstream ofs(filename.c_str(), ofstream::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << make_binary_object((Client*)client, sizeof(Client));
}

void load(Client *client, string filename) {
    ifstream ifs(filename.c_str(), ifstream::binary);
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia >> make_binary_object((Client*)client, sizeof(Client));
}

int main() {
    try {

        string filename = "client.dat";
        Client *client = new Client();
        load(client, filename);
        client->printClientInfo();

    }
    catch ( const exception &e ) {
        cerr << e.what() << endl;
    }

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp Client.cpp mainClient.cpp -o mainClient /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall