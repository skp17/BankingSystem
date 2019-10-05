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
    ia >> make_binary_object((Client*)client, sizeof(Account));
}

int main() {
    try {
        string filename = "client.dat";
        Date dateOfBirth(9, 10,1940);
        Client *client1 = new Client("John", "Lennon", dateOfBirth, 123456789, 4019);
        client1->setAddress("9 St-Catherine Est");
        client1->setTelephone("514-777-7777");
        client1->setEmail("jlennon@gmail.com");
        client1->setPIN(1111);
        client1->depositToAccount(101001, 725.50);
        client1->depositToAccount(201001, 50.50);
        client1->printClientInfo();

        save(client1, filename);
        
        Client *client2 = new Client();
        load(client2, filename);
        cout << "\n\n\nAfter loading archive";
        client2->printClientInfo();


    }
    catch ( const exception &e ) {
        cerr << e.what() << endl;
    }

    return 0;
}