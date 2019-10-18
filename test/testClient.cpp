#define BOOST_TEST_MODULE Client test
#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#include <boost/test/unit_test.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using uint = unsigned int;

const string filename = "client.dat";

BOOST_AUTO_TEST_CASE(Client_test)
{
    Date dateOfBirth(9, 10, 1940);
    Client client1("John", "Lennon", dateOfBirth, 123456789, "4019",
                   "9 St-Catherine Est", "514-777-7777", "jlennon@gmail.com");

    uint accessNumber;

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

    // test operator=
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

    // test validateLogin member function
    client1.setPIN("1111");
    BOOST_CHECK(client1.validateLogin(accessNumber, "1111") == true);

    // Perform transactions
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

    // Delete an account
    bool isdeleted = client1.deleteAccount(cheqAccountNumber);
    BOOST_CHECK(isdeleted == false);
    client1.withdrawFromAccount(cheqAccountNumber, 50.75);
    isdeleted = client1.deleteAccount(cheqAccountNumber);
    BOOST_CHECK(client1.getNumOfCheqAccounts() == 1);
    BOOST_CHECK(client1.getNumOfSavAccounts() == 2);
}

BOOST_AUTO_TEST_CASE(save_test)
{
    uint newAccountNum;

    // Client 1
    Date dateOfBirth(9, 10, 1940);
    Client client1("John", "Lennon", dateOfBirth, 123456789, "4019");
    client1.setAddress("9 St-Catherine Est");
    client1.setTelephone("514-777-7777");
    client1.setEmail("jlennon@gmail.com");
    newAccountNum = client1.createAccount(accountType::Chequing);
    client1.depositToAccount(newAccountNum, 200.25);
    newAccountNum = client1.createAccount(accountType::Savings);
    client1.depositToAccount(newAccountNum, 500.00);
    newAccountNum = client1.createAccount(accountType::Savings);
    client1.depositToAccount(newAccountNum, 10000.00);

    // Client 2
    Date dateOfBirth2(1, 5, 1996);
    Client client2("Peter", "Parker", dateOfBirth2, 987654321, "9619");
    client2.setAddress("69th Road, Forest Hills");
    client2.setTelephone("917-777-7777");
    client2.setEmail("parker@gmail.com");
    newAccountNum = client2.createAccount(accountType::Chequing);
    client2.depositToAccount(newAccountNum, 75.50);

    ofstream ofs(filename.c_str(), ios::binary);
    assert(ofs.good());
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << client1;
    oa << client2;
    ofs.close();
}

BOOST_AUTO_TEST_CASE(load_test)
{
    Client new_client1;
    Client new_client2;

    ifstream ifs(filename.c_str(), ios::binary);
    assert(ifs.good());
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia >> new_client1;
    ia >> new_client2;
    ifs.close();

    BOOST_CHECK(new_client1.getFName() == "John");
    BOOST_CHECK(new_client1.getLName() == "Lennon");
    BOOST_CHECK(new_client1.getAge() == 79);
    BOOST_CHECK(new_client1.getBirthDay() == 9);
    BOOST_CHECK(new_client1.getBirthMonth() == 10);
    BOOST_CHECK(new_client1.getBirthYear() == 1940);
    BOOST_CHECK(new_client1.getSSN() == 123456789);
    BOOST_CHECK(new_client1.getAddress() == "9 St-Catherine Est");
    BOOST_CHECK(new_client1.getTelephone() == "514-777-7777");
    BOOST_CHECK(new_client1.getEmail() == "jlennon@gmail.com");
    BOOST_CHECK(new_client1.getNumOfCheqAccounts() == 1);
    BOOST_CHECK(new_client1.getNumOfSavAccounts() == 2);

    uint accessNumber = new_client1.getAccessNum();
    BOOST_CHECK(new_client1.validateLogin(accessNumber, "4019") == true);

    BOOST_CHECK(new_client2.getFName() == "Peter");
    BOOST_CHECK(new_client2.getLName() == "Parker");
    BOOST_CHECK(new_client2.getAge() == 23);
    BOOST_CHECK(new_client2.getBirthDay() == 1);
    BOOST_CHECK(new_client2.getBirthMonth() == 5);
    BOOST_CHECK(new_client2.getBirthYear() == 1996);
    BOOST_CHECK(new_client2.getSSN() == 987654321);
    BOOST_CHECK(new_client2.getAddress() == "69th Road, Forest Hills");
    BOOST_CHECK(new_client2.getTelephone() == "917-777-7777");
    BOOST_CHECK(new_client2.getEmail() == "parker@gmail.com");
    BOOST_CHECK(new_client2.getNumOfCheqAccounts() == 1);
    BOOST_CHECK(new_client2.getNumOfSavAccounts() == 0);

    accessNumber = new_client2.getAccessNum();
    BOOST_CHECK(new_client2.validateLogin(accessNumber, "9619") == true);
}
// g++ -I /usr/local/boost_1_61_0/ -I ../source/ ../source/Date.cpp ../source/Person.cpp ../source/Account.cpp ../source/ChequingAccount.cpp ../source/SavingsAccount.cpp ../source/Client.cpp testClient.cpp -o testClient ../boost_serialization/libboost_serialization.a boost_test/libboost_unit_test_framework.a -std=c++11 -Wall