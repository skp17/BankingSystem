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

        client1.print();

        struct tm cd = client1.getAccDateCreation(101001);
        cout << "Chequing account created on: " << asctime( &cd ) << endl;
    }
    catch ( const exception &exc )
    {
        // catch anything thrown within try block that derives from std::exception
        cerr << exc.what();
    }


    return 0;
}