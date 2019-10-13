#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
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

BankManager BM;
const string filename = "bank.xml";

//functions
void wait();
void saveArchive(BankManager&);
bool loadArchive(BankManager&);
void getInput(uint&); 
void getInput(double&);
void loginSection();
bool extractDate(string&, Date&);
bool registration();
void editProfile(Client*);
void clientProfile(Client*);
bool deposit(Client*);
bool withdraw(Client*);
bool createAccount(Client*);
bool deleteAccount(Client*);


int main() { //////////////////////////////////////////////---Main---//////////////////////////////////////////////////////

    try {
        loadArchive(BM);
        
        char input;
        do {
            system("clear");
            cout << "Welcome to " << BM.getBankName() << endl;
            cout << "Options: \n";
            cout << "\t(1) Login to access accounts\n";
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

void wait() {
    char input;
    cout << "Enter any character to continue...\n";
    cin >> input;
}

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

void getInput(uint &input) {
    while ( !(cin >> input) ) {
        //clear bad input flag
        cin.clear();
        //discard input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input; please re-enter.\n";
        cout << "prompt> ";
    }
}

void getInput(double &input) {
    while ( !(cin >> input) ) {
        //clear bad input flag
        cin.clear();
        //discard input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input; please re-enter.\n";
        cout << "prompt> ";
    }
}

void loginSection() {
    system("clear");
    Client *client;
    uint accessNumber, pin;
    termios oldt, newt;
    bool valid = false;
    string input;

    do {
            cout << "***Enter 'r' at any moment to return to previous menu\n\n";
            cout << "Enter your access number: \n";
            if (isatty(STDIN_FILENO))
                cout << "prompt> ";
            cin >> input;

            if( input == "r") break;

            accessNumber = strtol(input.c_str(), nullptr, 10);
            
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
            pin = strtol(input.c_str(), nullptr, 10);
            
            /* Reset terminal */
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt);

            client = BM.getClient(typeID::accessNumber, accessNumber);
            if( client != nullptr ) {
                if( client->validateLogin(accessNumber, pin) ) {
                    valid = true;
                }
            }

            if(!valid)
                cout << "\n\nFailed to login\n\n";

    } while(!valid);

    if(valid)
        clientProfile(client);
}

bool extractDate(string &s, Date &dt) {
	// function expects the string in format dd/mm/yyyy:
    bool result;
	istringstream is(s);
	char delimiter;
	unsigned int d, m, y;

	if (is >> d >> delimiter >> m >> delimiter >> y) {
        dt.setDate(d, m, y);
        result = true;
	}
	else {
		cerr << "Invalid date format";
        result = false;
    }

	return result;
}

bool registration() {
    system("clear");
    bool active = true;
    termios oldt, newt;
    Client *newClient;
    string firstName, lastName;
    string stringDate; // dd/mm/yyyy
    int day, month, year;
    uint SSN;
    uint pin, confirmPIN;
    bool pinConfirmed = false;
    string address;
    string telephone;
    string email;
    Date dateOfBirth;
    bool result = false;

    cout << "In order for your to become a client at " << BM.getBankName()
        << " you will need to create a profile\n";
    cout << "Please enter your information below\n\n";
    
    cout << "Enter your firstname\n";
    cout << "prompt> ";
    cin >> firstName;
    cout << "Enter your lastname\n";
    cout << "prompt> ";
    cin >> lastName;
    cout << "Enter your date of birth in dd/mm/yyyy format\n";
    do {
        cout << "prompt> ";
        cin >> stringDate;
    } while ( !extractDate(stringDate, dateOfBirth) );
    cout << "Enter your social security number\n";
    cout << "prompt> ";
    getInput(SSN);
    cout << "Enter your home address\n";
    cout << "prompt> ";
    cin >> address;
    cout << "Enter your telephone number\n";
    cout << "prompt> ";
    cin >> telephone;
    cout << "Enter your email address\n";
    cout << "prompt> ";
    cin >> email;

    /* Turn echoing off */
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    do {
        cout << "Enter your pin\n";
        cout << "prompt> ";
        getInput(pin);
        cout << "Please confirm your pin\n";
        getInput(confirmPIN);
        if( pin == confirmPIN )
            pinConfirmed = true;
    } while(!pinConfirmed);

    /* Reset terminal */
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt);

    newClient = new Client( firstName, lastName, dateOfBirth, SSN, pin,
        address, telephone, email );
        cout << string(65, '-') << endl;
        cout << "Your access number is " << newClient->getAccessNum() << endl;
        cout << string(65, '-') << endl;

    char input;
    do {
        newClient->printClientInfo();
        cout << "Enter 'e' to edit your information or 's' to save\n";
        cout << "prompt> ";
        cin >> input;

        if( input == 'e' ) {
            editProfile(newClient);
        }
        else if( input == 's' ) {
            BM.addClient(newClient);
            result = true;
        }
    } while (input != 's');

    delete newClient;

    return result;
}

void editProfile(Client *client) {
    system("clear");
    client->printClientInfo();

}

void clientProfile(Client *client) {
    system("clear");
    char input;
    
    do {
        cout << "Welcome " << client->getName() <<"\n\n";
        cout << "\t(1) Make a deposit\n";
        cout << "\t(2) Make a withdrawal\n";
        cout << "\t(3) Create an account\n";
        cout << "\t(4) Delete an account\n";
        cout << "\t(5) Display banking information\n";
        cout << "\t(6) Edit banking profile information\n"; // set up
        cout << "\t(7) Delete banking profile (deletes all info and accounts if empty)\n"; // set up
        cout << "\t(8) Logout\n";
        cout << "\tSelect your option (1-8)\n";
        cout << "prompt> ";
        cin >> input;

        switch(input) {
            case '1':
                deposit(client);
                break;
            case '2':
                withdraw(client);
                break;
            case '3':
                createAccount(client);
                break;
            case '4':
                deleteAccount(client);
                break;
            case '5':
                cout << "\n\n";
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
    client->listAccounts();
    uint accountNumber;
    double amount;
    cout << "Enter the number of the account you would like to deposit to\n";
    cout << "prompt> ";
    getInput(accountNumber);
    cout << "Enter amount to deposit\n";
    cout << "prompt> ";
    getInput(amount);
    bool result = client->depositToAccount(
            accountNumber, amount);
    
    result?
        cout << "Deposit succsessful\n" :
        cout << "Deposit failed\n";

    return result;
}

bool withdraw(Client *client) {
    system("clear");
    client->listAccounts();
    uint accountNumber; 
    double amount;
    cout << "Enter the number of the account you would like to withdraw from\n";
    cout << "prompt> ";
    cin >> accountNumber;
    cout << "Enter amount to deposit\n";
    cout << "prompt> ";
    cin >> amount;
    bool result = client->withdrawFromAccount(
            accountNumber, amount);

    result?
        cout << "Withdrawal succsessful\n" :
        cout << "Withdrawal failed\n";

    return result;
}

bool createAccount(Client *client) {
    system("clear");
    bool active = true;
    char input;
    uint newAccountNumber;
    double amount;
    bool deposited;
    bool result = false;

    while(active) {
        cout << "Options:\n";
        cout << "\t(1) Create a checking account\n";
        cout << "\t(2) Create a savings account\n";
        cout << "\t(3) Return to previous menu\n";
        cout << "Select your option (1-3)\n";
        cout << "prompt> ";
        cin >> input;

        if(input == '1') {
            newAccountNumber = client->createAccount(accountType::Chequing);
            if (newAccountNumber == 0) {
                cout << "Error. Could not create account\n";
                break;
            }
            cout << "\nChequing Account created\n";
            cout << "Enter amount to deposit\n";
            cout << "prompt> ";
            getInput(amount);

            deposited = client->depositToAccount(
                newAccountNumber, amount);
            if(deposited) { 
                cout << "Deposit succsessful\n";
                result = true;
            }
            else
                cout << "Deposit failed\n";
            break;
        }
        if(input == '2') {
            newAccountNumber = client->createAccount(accountType::Savings);
            if (newAccountNumber == 0) {
                cout << "Error. Could not create account\n";
                break;
            }
            cout << "\nSavings Account created\n";
            cout << "Enter amount to deposit\n";
            cout << "prompt> ";
            getInput(amount);

            deposited = client->depositToAccount(
                newAccountNumber, amount);
            if(deposited) { 
                cout << "Deposit succsessful\n";
                result = true;
            }
            else
                cout << "Deposit failed\n";
            break;
        }
        if(input == '3')
                break;
        
    }

    if(result) {
        client->printAccount(newAccountNumber);
        cout << "\nEnter any character to return to previous menu\n";
        cin >> input;
    }
    return result;
}

bool deleteAccount(Client *client) {
    system("clear");
    uint accountNumber;
    bool result = false;

    client->listAccounts();
    cout << "Enter the account number of the account you want to delete\n";
    cout << "prompt> ";
    getInput(accountNumber);
    result = client->deleteAccount(accountNumber);

    if(result)
        cout << "account deleted\n";

    return result;
}

// g++ -I /usr/local/boost_1_61_0/ Date.cpp Person.cpp Account.cpp ChequingAccount.cpp SavingsAccount.cpp Client.cpp BankManager.cpp banksystem.cpp -o banksystem /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall

