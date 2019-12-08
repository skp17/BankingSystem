#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <termios.h>
#include <stdlib.h> 
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
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
const string filename = "bank.dat";

//functions
void Pause();
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
            cout << "\t(3) Exit\n";
            cout << "\n\tSelect your option (1-3)\n";
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

void Pause() {
  cout << endl << "Press any key to continue...";
  cin.ignore();
  getchar();
}

void saveArchive(BankManager &BM) {
    //cout << "Saving...\n";
    ofstream ofs(filename.c_str(), ios::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << BM;
}

bool loadArchive(BankManager &BM) {
    bool result = false;
    ifstream ifs(filename.c_str(), ios::binary);
    if ( ifs.is_open() ) {
        cout << "Loading...\n";
        boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
        ia >> BM;
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

string read4DigitPIN()
{
    bool ok = true;
    string result;
    while (ok) {
    
        cin >> result;
        if (result.length() == 4) 
        {
            bool allDigits = true;
            for(unsigned index = 0; index < 4; ++index)
            {
                allDigits = allDigits && ( 
                    (result[index] >= '0') && 
                    (result[index] <='9') 
                    );
            }
            if(allDigits)	
            	break;
            else {
            	cerr << "\nPIN must be between 0000 and 9999. Please try again\n";
            	cout << "prompt> ";
            }
        }
        else {
        	cerr << "\nPIN must be 4 digits. Please try again\n";
        	cout << "prompt> ";
        }
    }
    return result;
}

void loginSection() {
    system("clear");
    Client *client;
    uint accessNumber;
    string pin;
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
        accessNumber = strtoul(input.c_str(), nullptr, 10);
            
        cout << "Enter your pin: \n";
        if (isatty(STDIN_FILENO))
            cout << "prompt> ";

        /* Turn echoing off */
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            
        /* Read pin */
        pin = read4DigitPIN();
            
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
        result = dt.setDate(d, m, y);   // Returns true if date is valid, else false.
	}
	else {
		cerr << "Invalid date format\n";
        //cerr << "Please enter you date of birth in mm/dd/yyyy format\n";
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
    uint SSN;
    string pin, confirmPIN; 
    bool pinConfirmed = false;
    string address;
    string telephone;
    string email;
    Date dateOfBirth;
    bool result = false;

    cout << "In order for your to become a client at " << BM.getBankName()
        << ", you will need to create a profile.\n";
    cout << "Please enter your information below.\n\n";
    
    cout << "Enter your first name\n";
    cout << "prompt> ";
    getline(cin >> ws, firstName);
    cout << "Enter your last name\n";
    cout << "prompt> ";
    getline(cin >> ws, lastName);
    do {
        cout << "Enter your date of birth in dd/mm/yyyy format\n";
        cout << "prompt> ";
        cin >> stringDate;
    } while ( !extractDate(stringDate, dateOfBirth) );
    cout << "Enter your social security number\n";
    cout << "prompt> ";
    getInput(SSN);
    cout << "Enter your home address\n";
    cout << "prompt> ";
    getline(cin >> ws, address);
    cout << "Enter your telephone number\n";
    cout << "prompt> ";
    getline(cin >> ws, telephone);
    cout << "Enter your email address\n";
    cout << "prompt> ";
    getline(cin >> ws, email);

    /* Turn echoing off */
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    do {
        cout << "Enter your pin\n";
        cout << "prompt> ";
        pin = read4DigitPIN();
        cout << "\nPlease confirm your pin\n";
        confirmPIN = read4DigitPIN();
        if( pin == confirmPIN )
            pinConfirmed = true;
        else
            cerr << "\nError: PIN is not the same\nPlease try again\n\n";
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
            if( BM.addClient(newClient) ){
                result = true;
                cout << "\nYou are now registered with " << BM.getBankName() << ".";
                cout << " The next step is to login and open an account.\n";
                saveArchive(BM);
            }
            else
                cerr << "\nCould not register.\n";
            Pause();
        }
    } while (input != 's');

    delete newClient;

    return result;
}

void editProfile(Client *client) {
    bool active = true;
    string str;
    char input;
    Date date;

    do {
        system("clear");
        cout << "-----Edit Profile-----\n\n";
        client->printPersonInfo();
        cout << "\n\t(1) Edit first name\n";
        cout << "\t(2) Edit last name\n";
        cout << "\t(3) Edit date of birth\n";
        cout << "\t(4) Edit address\n";
        cout << "\t(5) Edit telephone\n";
        cout << "\t(6) Edit email\n";
        cout << "\t(7) Return to previous menu\n";
        cout << "\n\tSelect your option (1-7)\n";
        cout << "prompt> ";
        cin >> input;
        cin.ignore();

        switch(input) {
            case '1':
                system("clear");
                cout << "Edit first name and save\n";
                cout << "prompt> ";
                cin >> str;
                client->setFName(str);
                cout << "\nProfile updated\n";
                break;
            case '2':
                system("clear");
                cout << "Edit last name and save\n";
                cout << "prompt> ";
                cin >> str;
                client->setLName(str);
                cout << "\nProfile updated\n";
                break;
            case '3':
                system("clear");
                cout << "Edit date of birth and save\n";
                do {
                    cout << "prompt> ";
                    cin >> str;
                } while ( !extractDate(str, date) );
                client->setDateofBirth(date);
                cout << "\nProfile updated\n";
                break;
            case '4':
                system("clear");
                cout << "Edit address and save\n";
                cout << "prompt> ";
                getline(cin, str);
                client->setAddress(str);
                cout << "\nProfile updated\n";
                break;
            case '5':
                system("clear");
                cout << "Edit telephone number and save\n";
                cout << "prompt> ";
                getline(cin, str);
                client->setTelephone(str);
                cout << "\nProfile updated\n";
                break;
            case '6':
                system("clear");
                cout << "Edit email and save\n";
                cout << "prompt> ";
                getline(cin, str);
                client->setEmail(str);
                cout << "\nProfile updated\n";
                break;
            case '7':
                active = false;
                break;
            default:
                cout << "Invalid Input\n";
                break;
        }


    } while(active);

}

void clientProfile(Client *client) {
    system("clear");
    char input;
    string str;
    bool active;
    bool isDeleted = false;
    bool exit = false;

    do {
        cout << "Welcome " << client->getName() <<"\n\n";
        cout << "\t(1) Make a deposit\n";
        cout << "\t(2) Make a withdrawal\n";
        cout << "\t(3) Create an account\n";
        cout << "\t(4) Delete an account\n";
        cout << "\t(5) Display banking information\n";
        cout << "\t(6) Edit banking profile information\n";
        cout << "\t(7) Delete banking profile (deletes all info and accounts if empty)\n"; // set up
        cout << "\t(8) Logout\n";
        cout << "\n\tSelect your option (1-8)\n";
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
                break;
            case '6':
                editProfile(client);
                saveArchive(BM);
                system("clear");
                break;
            case '7':
                cout << "\nAre you sure you want to delete your profile.";
                cout << " All of your information and empty bank accounts will be deleted.\n";
                cout << "Enter 'Yes' to proceed\n";
                cout << "Enter 'no' to return\n";
                active = true;
                while(active) {
                    cout << "prompt> ";
                    cin >> str;
                    if(str == "Yes") {
                        isDeleted = BM.removeClient( client->getAccessNum() );
                        active = false;
                    } else if (str == "no") {
                        active = false;
                    } else
                        cerr << "\nInvalid input\n";
                }

                if(str == "Yes" && isDeleted) {
                    cout << "\nAll of your information and accounts have been deleted. We are sad to see you go.\n";
                    Pause();
                    exit = true;
                } else if(str == "Yes" && !isDeleted) {
                    cout << "\nProfile could not be deleted\n";
                    Pause();
                }
                
                break;
            case '8':
                exit = true;
                break;
            default:
                cout << "Invalid input\n";
        }

    } while( !exit );

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
    
    if(result) {
        cout << "Deposit succsessful\n";
        saveArchive(BM);
    }
    else
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
    getInput(accountNumber);
    cout << "Enter amount to deposit\n";
    cout << "prompt> ";
    getInput(amount);
    bool result = client->withdrawFromAccount(
            accountNumber, amount);

    if(result) {
        cout << "Deposit succsessful\n";
        saveArchive(BM);
    }
    else
        cout << "Deposit failed\n";

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
        cout << "\n\tSelect your option (1-3)\n";
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
                cout << "\nDeposit succsessful\n";
                saveArchive(BM);
                result = true;
            }
            else
                cout << "\nDeposit failed\n";
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
                cout << "\nDeposit succsessful\n";
                saveArchive(BM);
                result = true;
            }
            else
                cout << "\nDeposit failed\n";
            break;
        }
        if(input == '3')
                break;
        
    }

    if(result) {
        client->printAccount(newAccountNumber);
        Pause();
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

    if(result) {
        cout << "account deleted\n";
        saveArchive(BM);
    }

    return result;
}
