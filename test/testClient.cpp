#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#define BOOST_TEST_MODULE Client test
#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace std;
using uint = unsigned int;

Date dateOfBirth(9, 10, 1940);
Client client1("John", "Lennon", dateOfBirth, 123456789, "4019",
               "9 St-Catherine Est", "514-777-7777", "jlennon@gmail.com");

uint accessNumber;

BOOST_AUTO_TEST_CASE(contructor_test)
{
    /* Get current time */
    time_t now = time(0);
    struct tm *t_now = localtime(&now);

    uint cheqAccountNumber;

    BOOST_CHECK(client1.getFName() == "John");
    BOOST_CHECK(client1.getLName() == "Lennon");
    BOOST_CHECK(client1.getBirthDay() == 9);
    BOOST_CHECK(client1.getBirthMonth() == 10);
    BOOST_CHECK(client1.getBirthYear() == 1940);
    BOOST_CHECK(client1.getAge() == 79);
    BOOST_CHECK(client1.getSSN() == 123456789);
    BOOST_CHECK(client1.getAddress() == "9 St-Catherine Est");
    BOOST_CHECK(client1.getTelephone() == "514-777-7777");
    BOOST_CHECK(client1.getEmail() == "jlennon@gmail.com");

    BOOST_CHECK(client1.getNumOfCheqAccounts() == 0);
    BOOST_CHECK(client1.getNumOfSavAccounts() == 0);

    accessNumber = client1.getAccessNum();
    BOOST_CHECK(client1.validateLogin(accessNumber, "4019") == true);

    //client1.listsAccounts();
}

BOOST_AUTO_TEST_CASE(assignment_test)
{
    Client client2 = client1;

    BOOST_CHECK(client2.getFName() == "John");
    BOOST_CHECK(client2.getLName() == "Lennon");
    BOOST_CHECK(client2.getBirthDay() == 9);
    BOOST_CHECK(client2.getBirthMonth() == 10);
    BOOST_CHECK(client2.getBirthYear() == 1940);
    BOOST_CHECK(client2.getAge() == 79);
    BOOST_CHECK(client2.getSSN() == 123456789);
    BOOST_CHECK(client2.getAddress() == "9 St-Catherine Est");
    BOOST_CHECK(client2.getTelephone() == "514-777-7777");
    BOOST_CHECK(client2.getEmail() == "jlennon@gmail.com");

    BOOST_CHECK(client2.getNumOfCheqAccounts() == 0);
    BOOST_CHECK(client2.getNumOfSavAccounts() == 0);
}

BOOST_AUTO_TEST_CASE(validateLogin_test)
{
    client1.setPIN("1111");
    BOOST_CHECK(client1.validateLogin(accessNumber, "1111") == true);
}

uint cheqAccountNumber;
BOOST_AUTO_TEST_CASE(transactions_test)
{
    uint newAccountNumber;
    newAccountNumber = client1.createAccount(accountType::Chequing);
    client1.depositToAccount(newAccountNumber, 525.25);

    newAccountNumber = client1.createAccount(accountType::Savings);
    client1.depositToAccount(newAccountNumber, 225.25);
    client1.withdrawFromAccount(newAccountNumber, 125.25);
    BOOST_CHECK(client1.getAccBalance(newAccountNumber) == (225.25 - 125.25));

    // Overdraft
    client1.withdrawFromAccount(newAccountNumber, 200.00);

    cheqAccountNumber = client1.createAccount(accountType::Chequing);
    BOOST_CHECK(client1.getNumOfCheqAccounts() == 2);
    BOOST_CHECK(client1.getNumOfSavAccounts() == 1);
    BOOST_CHECK(client1.getAccBalance(cheqAccountNumber) == 0);
    client1.depositToAccount(cheqAccountNumber, 50.75);
    BOOST_CHECK(client1.getAccBalance(cheqAccountNumber) == 50.75);

    uint newAccNum = client1.createAccount(accountType::Savings);
    BOOST_CHECK(client1.getNumOfCheqAccounts() == 2);
    BOOST_CHECK(client1.getNumOfSavAccounts() == 2);
    BOOST_CHECK(client1.getAccBalance(newAccNum) == 0);
    client1.depositToAccount(newAccNum, 90.20);
    BOOST_CHECK(client1.getAccBalance(newAccNum) == 90.20);
}

BOOST_AUTO_TEST_CASE(delete_account_test)
{
    bool isdeleted = client1.deleteAccount(cheqAccountNumber);
    BOOST_CHECK(isdeleted == false);
    client1.withdrawFromAccount(cheqAccountNumber, 50.75);
    isdeleted = client1.deleteAccount(cheqAccountNumber);
    BOOST_CHECK(client1.getNumOfCheqAccounts() == 1);
    BOOST_CHECK(client1.getNumOfSavAccounts() == 2);
}

// g++ -I /usr/local/boost_1_61_0/ -I ../source/ ../source/Date.cpp ../source/Person.cpp ../source/Account.cpp ../source/ChequingAccount.cpp ../source/SavingsAccount.cpp ../source/Client.cpp testClient.cpp -o testClient ../boost_serialization/libboost_serialization.a boost_test/libboost_unit_test_framework.a -std=c++11 -Wall