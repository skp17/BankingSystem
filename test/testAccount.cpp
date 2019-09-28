#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../Account.h"
#include "../ChequingAccount.h"
#include "../SavingsAccount.h"
#include <ctime>

using namespace std;

TEST_CASE( "Banking accounts can be created" ) {
    SECTION( "Open a checking account" ) {
        ChequingAccount c;
        time_t now = time(0);
        struct tm *t_now = localtime(&now); // Get current time
        
        REQUIRE( c.getDateCreated().tm_year == t_now->tm_year );
        REQUIRE( c.getDateCreated().tm_mon == t_now->tm_mon );
        REQUIRE( c.getDateCreated().tm_mday == t_now->tm_mday);
        REQUIRE( c.getBalance() == 0);
        c.print();

        SECTION( "Perform transactions" ) {
            c.deposit(100.50);
            c.print();
            REQUIRE( c.getBalance() == 100.5);
            c.withdraw(50);
            REQUIRE( c.getBalance() == 50.5);
            c.print();
        }

        SECTION( "When withdraw amount exceeds balance") {
            try {
                c.withdraw(100);
            }
            catch( invalid_argument &e) {
                cout << "Exception: " << e.what() << endl;
            }
        }
        
    }
}


