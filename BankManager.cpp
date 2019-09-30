#include <iostream>
#include <string>
#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"

using namespace std;

int main() {

    // Keep track of SSN to avoid duplicates

    try {

    }
    catch( invalid_argument &e ) {
        cerr << "Exception: " << e.what() << endl << endl;
    }
    catch( bad_alloc &e ) {
        cerr << "Exception: " << e.what() << endl << endl;
    }
    catch ( string &e) {
        cerr << "Exception: " << e << endl << endl;
    }
    catch ( const exception &exc )
    {
        // catch anything thrown within try block that derives from std::exception
        cerr << exc.what();
    }


    return 0;
}
