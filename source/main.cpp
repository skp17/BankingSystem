#include <iostream>
#include <string>
#include "Date.h"
#include "Client.h"

using namespace std;
using uint = unsigned int;

int main() {

    try {
        Date dateOfBirth(9, 10,1940);
        Client client1("John", "Lennon", dateOfBirth, 123456789, 4019);
        client1.setAddress("9 St-Catherine Est").setTelephone("514-777-7777");
        client1.setEmail("jlennon@gmail.com");

        //client1.print();
        //client1.listsAccounts();

        // Perform transactions
        cout << "Make a deposit\n";
        client1.depositToAccount(101001, 525.25);
        //client1.listsAccounts();

        cout << "Make a withdrawal\n";
        if ( !client1.withdrawFromAccount(201001, 125.25) );
            cout << "Withdrawal unsucessful\n\n";
        //client1.listsAccounts();

        //client1.print();

        struct tm cd = client1.getAccDateCreation(101001);
        //cout << "Chequing account created on: " << asctime( &cd ) << endl;

        uint newAccNum = client1.createAccount(accountType::Chequing);
        if( client1.getNumOfCheqAccounts() != 2 ) cout << "problem at line 36\n";

        if( client1.getNumOfSavAccounts() != 1 ) cout << "problem at line 38\n"; 

        if( client1.getAccBalance(newAccNum) != 0 ) cout << "problem at line 40\n";

        client1.depositToAccount(newAccNum, 50.75);
        if( client1.getAccBalance(newAccNum) != 50.75 ) cout << "problem at line 43\n";
            
        newAccNum = client1.createAccount(accountType::Savings);
        if( client1.getNumOfCheqAccounts() != 2 ) cout << "problem at line 46\n";

        if( client1.getNumOfSavAccounts() != 2 ) cout << "problem at line 48\n";

        if( client1.getAccBalance(newAccNum) != 0 ) cout << "problem at line 50\n";

        client1.depositToAccount(newAccNum, 90.20);
        if( client1.getAccBalance(newAccNum) != 90.20 ) cout << "problem at line 53\n";

        client1.print();
    }
    catch ( const exception &exc )
    {
        // catch anything thrown within try block that derives from std::exception
        cerr << exc.what();
    }


    return 0;
}