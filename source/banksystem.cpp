#include "Date.h"
#include "Person.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include "Client.h"
#include "BankManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <termios.h>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;
using boost::serialization::make_binary_object;

const string filename = "bank.dat";

BankManager *BM;

void saveArchive(BankManager BM) {
    cout << "Saving...\n";
    ofstream ofs(filename.c_str(), ofstream::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << make_binary_object((BankManager*)&BM, sizeof(BankManager));
}

bool loadArchive(BankManager *BM) {
    bool result = false;
    ifstream ifs(filename.c_str(), ifstream::binary);
    if ( ifs.is_open() ) {
        cout << "Loading...\n";
        boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
        ia >> make_binary_object((BankManager*)BM, sizeof(BankManager));
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


            if( BM->getClient(typeID::accessNumber, accessNumber)->
                validateLogin(accessNumber, pin) ) {
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
        BM = new BankManager;
        loadArchive(BM);
        
        string input = "";
        while(1) {
            cout << "Options: \n";
            cout << "\tEnter 'login' to access acounts.\n";
            cout << "\tEnter 'new' to become a client at " << BM->getBankName() << ".\n";
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

