#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include <ctime>
#include <exception>

using namespace std;
using uint = unsigned int;

TEST_CASE( "Create a new client" ) {

    try{
        /* Get current time */
        time_t now = time(0);
        struct tm *t_now = localtime(&now);

        Date dateOfBirth(9, 10,1940);
        Client client1("John", "Lennon", dateOfBirth, 123456789, 4019, 
        "9 St-Catherine Est", "514-777-7777", "jlennon@gmail.com");

        REQUIRE( client1.getFName() == "John" );
        REQUIRE( client1.getLName() == "Lennon" );
        REQUIRE( client1.getBirthDay() == 9 );
        REQUIRE( client1.getBirthMonth() == 10 );
        REQUIRE( client1.getBirthYear() == 1940 );
        REQUIRE( client1.getAge() == 78 );
        REQUIRE( client1.getSSN() == 123456789 );
        REQUIRE( client1.getAddress() == "9 St-Catherine Est");
        REQUIRE( client1.getTelephone() == "514-777-7777");
        REQUIRE( client1.getEmail() == "jlennon@gmail.com");

        REQUIRE( client1.getNumOfCheqAccounts() == 0);
        REQUIRE( client1.getNumOfSavAccounts() == 0);

        uint accessNumber = client1.getAccessNum();
        REQUIRE( client1.validateLogin(accessNumber, 4019) == true );

        client1.listsAccounts();

        SECTION( "Copy client object") {
            Client client2 = client1;

            REQUIRE( client2.getFName() == "John" );
            REQUIRE( client2.getLName() == "Lennon" );
            REQUIRE( client2.getBirthDay() == 9 );
            REQUIRE( client2.getBirthMonth() == 10 );
            REQUIRE( client2.getBirthYear() == 1940 );
            REQUIRE( client2.getAge() == 78 );
            REQUIRE( client2.getSSN() == 123456789 );
            REQUIRE( client2.getAddress() == "9 St-Catherine Est");
            REQUIRE( client2.getTelephone() == "514-777-7777");
            REQUIRE( client2.getEmail() == "jlennon@gmail.com");

            REQUIRE( client2.getNumOfCheqAccounts() == 0);
            REQUIRE( client2.getNumOfSavAccounts() == 0);
        }

    
        SECTION( "Change pin" ) {
            client1.setPIN(1111);
            REQUIRE( client1.validateLogin(accessNumber, 1111) == true );
        }
        /*
        SECTION( "Perform transactions" ) {
            client1.depositToAccount(101004, 525.25);
            client1.depositToAccount(201004, 100.00);
            client1.withdrawFromAccount(101001, 125.25);
            REQUIRE( client1.getAccBalance(101001) == (525.25-125.25));
            // Overdraft
            client1.withdrawFromAccount(201004, 200.00);
        }
        */
        
        SECTION( "Create another account") {
            uint newAccNum = client1.createAccount(accountType::Chequing);
            REQUIRE( client1.getNumOfCheqAccounts() == 2);
            REQUIRE( client1.getNumOfSavAccounts() == 1);
            REQUIRE( client1.getAccBalance(newAccNum) == 0);
            client1.depositToAccount(newAccNum, 50.75);
            REQUIRE( client1.getAccBalance(newAccNum) == 50.75);
            
            newAccNum = client1.createAccount(accountType::Savings);
            REQUIRE( client1.getNumOfCheqAccounts() == 2);
            REQUIRE( client1.getNumOfSavAccounts() == 2);
            REQUIRE( client1.getAccBalance(newAccNum) == 0);
            client1.depositToAccount(newAccNum, 90.20);
            REQUIRE( client1.getAccBalance(newAccNum) == 90.20);
        }
        

        SECTION( "Delete account" ) {

        }


    }
    catch( invalid_argument &e ) {
        cerr << "Exception: " << e.what() << endl << endl;
    }
    catch( bad_alloc &e ) {
        cerr << "Exception: " << e.what() << endl << endl;
    }
    catch( const exception &e) {
        cerr << "Exception: " << e.what() << endl << endl;
    }
} 

// g++ -I /usr/local/boost_1_61_0/ -I ../source/ ../source/Date.cpp ../source/Person.cpp ../source/Account.cpp ../source/ChequingAccount.cpp ../source/SavingsAccount.cpp ../source/Client.cpp  testClient.cpp -o testClient /usr/local/boost_1_61_0/bin.v2/libs/serialization/build/gcc-5.4.0/release/link-static/threading-multi/libboost_serialization.a -std=c++11 -Wall