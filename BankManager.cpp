#include <iostream>
#include <string>
#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"

using namespace std;

int main() {

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


    return 0;
}
