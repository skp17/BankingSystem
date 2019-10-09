#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
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

BankManager BM;
const string filename = "bank.xml";

void saveArchive(BankManager &BM) {
    cout << "Saving...\n";
    ofstream ofs(filename.c_str());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(BM);
}

bool loadArchive(BankManager &BM) {
    bool result = false;
    ifstream ifs(filename.c_str());
    if ( ifs.is_open() ) {
        cout << "Loading...\n";
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(BM);
        result = true;
    }

    return result;
}

bool loginSection() {
    uint accessNumber, pin;
    termios oldt, newt;
    bool valid = false;
    string input;

    cout << "\nEnter 'return' at anytime to go back\n\n";

    do {
            cout << "Enter your access number: \n";
            if (isatty(STDIN_FILENO))
                cout << "prompt> ";
            cin >> input;

            if( input == "return") break;

            accessNumber = stoi(input);
            
            cout << "Enter your pin: \n";
            if (isatty(STDIN_FILENO))
                cout << "prompt> ";

            /* Turn echoing off */
            tcgetattr(STDIN_FILENO, &oldt);
            termios newt = oldt;
            newt.c_lflag &= ~ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            
            /* Read pin */
            cin >> input;
            pin = stoi(input);
            
            /* Reset terminal */
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt);


            if( BM.getClient(typeID::accessNumber, accessNumber)
                ->validateLogin(accessNumber, pin) ) 
            {
                valid = true;
            }
            else {
                cout << "Failed to login.\n";
            }
    } while(!valid);

    if(valid)
        cout << "logged in\n";

    return valid;
}

bool registration() {

}

bool clientProfile() {

}


int main() {

    try {
        loadArchive(BM);
        BM.print();
        
        string input = "";
        while(1) {
            cout << "Options: \n";
            cout << "\tEnter 'login' to access acounts.\n";
            cout << "\tEnter 'new' to become a client at " << BM.getBankName() << ".\n";
            cout << "\tEnter 'exit' to quit.\n\n";
            cout << "prompt> ";
            cin >> input;

            if( input == "login" ) {
                loginSection();
            } 
            else if( input == "new" ) {
                registration();
            }
            else if( input == "exit") {
                break;
            }
            else
                cerr << "Invalid input\n\n";

            

        }

        //saveArchive(BM);

    }
    catch( const exception &e ) {
        cerr << "Exception: "  << e.what() << "\n\n";
    }

    return 0;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp Client.cpp BankManager.cpp banksystem.cpp -o banksystem /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall

