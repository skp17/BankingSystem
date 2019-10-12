#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <stdlib.h> 
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

void wait() {
    char input;
    cout << "Enter a character to continue...";
    cin >> input;
}

BankManager BM;
const string filename = "bank.xml";

void saveArchive(BankManager&);

bool loadArchive(BankManager&);

void loginSection();

void registration();

void clientProfile(Client*);

bool deposit(Client*);

bool withdraw(Client*);

bool createAccount(Client*);

bool deleteAccount(Client*);


int main() { ///////////////////////////////////////////////////////---Main---//////////////////////////////////////////////////////

    try {
        loadArchive(BM);
        
        char input;
        do {
            system("clear");
            cout << "Options: \n";
            cout << "\t(1) Login to access acounts\n";
            cout << "\t(2) Become a client at " << BM.getBankName() << endl;
            cout << "\t(3) Exit\n\n";
            cout << "\tSelect your option (1-3)\n";
            cout << "prompt> ";
            cin >> input;
            system("clear");

            switch(input) {
                case '1':
                    loginSection();
                    break;
                case '2':
                    registration();
                    break;
                case '3':
                    cout << "Thank you for using " << BM.getBankName() << endl;
                    break;
                default:
                    cout << "Invalid input\n";
            }

        } while(input != '3');

    }
    catch( const exception &e ) {
        cerr << "Exception: "  << e.what() << "\n\n";
    }

    saveArchive(BM);
    return 0;
} /////////////////////////////////////////////////////////---Main---////////////////////////////////////////////////////////////

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

void loginSection() {
    system("clear");
    Client *client;
    uint accessNumber, pin;
    termios oldt, newt;
    bool valid = false;
    string input;

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

            client = BM.getClient(typeID::accessNumber, accessNumber);
            if( client != nullptr ) {
                if( client->validateLogin(accessNumber, pin) ) {
                    valid = true;
                }
            }

            if(!valid)
                cout << "Failed to login\n\n";

    } while(!valid);

    if(valid)
        clientProfile(client);
}

void registration() {

}

void clientProfile(Client *client) {
    system("clear");
    cout << "Welcome\n\n";
    client->printClientInfo();
    char input;
    
    do {
        cout << "\t(1) Make a deposit\n";
        cout << "\t(2) Make a withdrawal\n";
        cout << "\t(3) Create an account\n";
        cout << "\t(4) Delete an account\n";
        cout << "\t(5) Display banking information\n";
        cout << "\t(6) Logout\n";
        cout << "\tSelect your option (1-6)\n";
        cout << "prompt> ";
        cin >> input;

        switch(input) {
            case '1':
                deposit(client)?
                    cout << "Deposit succsessful\n" :
                    cout << "Deposit failed\n";
                    break;
            case '2':
                withdraw(client)?
                    cout << "Withdrawal succsessful\n" :
                    cout << "Withdrawal failed\n";
                    break;
            case '3':
                createAccount(client);
                break;
            case '4':
                deleteAccount(client);
                break;
            case '5':
                client->printClientInfo();
            case '6':
                break;
            default:
                cout << "Invalid input\n";
        }

    } while(input != '6');

}

bool deposit(Client *client) {
    system("clear");
    uint accountNumber, amount;
    cout << "Enter account number\n";
    cout << "prompt> ";
    cin >> accountNumber;
    cout << "Enter amount to deposit\n";
    cout << "prompt> ";
    cin >> amount;
    bool result = client->depositToAccount(
            accountNumber,
            amount);
    return result;
}

bool withdraw(Client *client) {
    system("clear");
    uint accountNumber, amount;
    cout << "Enter account number\n";
    cout << "prompt> ";
    cin >> accountNumber;
    cout << "Enter amount to deposit\n";
    cout << "prompt> ";
    cin >> amount;
    bool result = client->withdrawFromAccount(
            accountNumber,
            amount);
    return result;
}

bool createAccount(Client*) {
    cout << "account created\n";
}

bool deleteAccount(Client*) {
    cout << "account deleted\n";
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp Client.cpp BankManager.cpp banksystem.cpp -o banksystem /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall

