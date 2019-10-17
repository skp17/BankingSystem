#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#define BOOST_TEST_MODULE Account test
#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace std;
using uint = unsigned int;

BOOST_AUTO_TEST_CASE(chequingAccount_test)
{

    ChequingAccount c;
    time_t now = time(0);
    struct tm *t_now = localtime(&now); // Get current time

    BOOST_CHECK(c.getDateCreated().getYear() == t_now->tm_year + 1900);
    BOOST_CHECK(c.getDateCreated().getMonth() == t_now->tm_mon + 1);
    BOOST_CHECK(c.getDateCreated().getDay() == t_now->tm_mday);
    BOOST_CHECK(c.getBalance() == 0);
    c.print();

    c.deposit(100.50);
    c.print();
    BOOST_CHECK(c.getBalance() == 100.5);
    c.withdraw(50);
    BOOST_CHECK(c.getBalance() == 50.5);
    c.print();

    c.withdraw(100);
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
    s.print();

    s.deposit(100.50);
    s.print();
    BOOST_CHECK(s.getBalance() == 100.5);
    s.withdraw(50);
    BOOST_CHECK(s.getBalance() == 50.5);
    s.print();

    s.withdraw(100);
}

// g++ -I /usr/local/boost_1_61_0/ -I ../source/ ../source/Date.cpp ../source/Person.cpp ../source/Account.cpp ../source/ChequingAccount.cpp ../source/SavingsAccount.cpp testAccount.cpp -o testAccount ../boost_serialization/libboost_serialization.a boost_test/libboost_unit_test_framework.a -std=c++11 -Wall