#define BOOST_TEST_MODULE Account test
#include <boost/test/unit_test.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
BOOST_CLASS_EXPORT(ChequingAccount);
#include "SavingsAccount.h"
BOOST_CLASS_EXPORT(SavingsAccount);
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using uint = unsigned int;

const string filename = "account.dat";

time_t now = time(0);
struct tm *t_now = localtime(&now); // Get current time

void save(Account &acc)
{
    ofstream ofs(filename.c_str(), ios::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << acc;
}

bool load(Account &acc)
{
    bool result = false;
    ifstream ifs(filename.c_str(), ios::binary);
    if (ifs.is_open())
    {
        boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
        ia >> acc;
        result = true;
    }

    return result;
}

BOOST_AUTO_TEST_CASE(chequingAccount_test)
{
    ChequingAccount c;

    BOOST_CHECK(c.getDateCreated().getYear() == t_now->tm_year + 1900);
    BOOST_CHECK(c.getDateCreated().getMonth() == t_now->tm_mon + 1);
    BOOST_CHECK(c.getDateCreated().getDay() == t_now->tm_mday);
    BOOST_CHECK(c.getBalance() == 0);

    c.deposit(100.50);
    BOOST_CHECK(c.getBalance() == 100.50);
    c.withdraw(50);
    BOOST_CHECK(c.getBalance() == 50.50);

    c.withdraw(100);
    c.print();

    // save account
    save(c);
}

BOOST_AUTO_TEST_CASE(savingsAccount_test)
{
    SavingsAccount s;
    time_t now = time(0);
    struct tm *t_now = localtime(&now); // Get current time

    BOOST_CHECK(s.getDateCreated().getYear() == t_now->tm_year + 1900);
    BOOST_CHECK(s.getDateCreated().getMonth() == t_now->tm_mon + 1);
    BOOST_CHECK(s.getDateCreated().getDay() == t_now->tm_mday);
    BOOST_CHECK(s.getBalance() == 0);

    s.deposit(100.50);
    BOOST_CHECK(s.getBalance() == 100.50);

    s.withdraw(100);
    BOOST_CHECK(s.getBalance() == 0.50);

}

BOOST_AUTO_TEST_CASE(load_test)
{
    Account *c = new ChequingAccount;
    load(*c);

    BOOST_CHECK(c->getDateCreated().getYear() == t_now->tm_year + 1900);
    BOOST_CHECK(c->getDateCreated().getMonth() == t_now->tm_mon + 1);
    BOOST_CHECK(c->getDateCreated().getDay() == t_now->tm_mday);
    BOOST_CHECK(c->getBalance() == 50.50);

    delete c;
}