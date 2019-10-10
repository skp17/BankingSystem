#include "Date.h"
#include "Client.h"
#include "Account.h"
#include "ChequingAccount.h"
#include "SavingsAccount.h"
#define BOOST_TEST_MODULE Client test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( my_test )
{
    Date date(10,10,2019);

    Date dateOfBirth(9, 10,1940);
    Client client1("John", "Lennon", dateOfBirth, 123456789, 4019, 
    "9 St-Catherine Est", "514-777-7777", "jlennon@gmail.com");

        BOOST_CHECK_EQUAL( client1.getFName() , "John" );
        BOOST_CHECK_EQUAL( client1.getLName() , "Lennon" );
        BOOST_CHECK_EQUAL( client1.getBirthDay() , 9 );
        BOOST_CHECK_EQUAL( client1.getBirthMonth() , 10 );
        BOOST_CHECK_EQUAL( client1.getBirthYear() , 1940 );
        BOOST_CHECK_EQUAL( client1.getAge() , 79 );
        BOOST_CHECK_EQUAL( client1.getSSN() , 123456789 );
        BOOST_CHECK_EQUAL( client1.getAddress() , "9 St-Catherine Est");
        BOOST_CHECK_EQUAL( client1.getTelephone() , "514-777-7777");
        BOOST_CHECK_EQUAL( client1.getEmail() , "jlennon@gmail.com");

        BOOST_CHECK_EQUAL( client1.getNumOfCheqAccounts() , 0);
        BOOST_CHECK_EQUAL( client1.getNumOfSavAccounts() , 0);

        uint accessNumber = client1.getAccessNum();
        BOOST_CHECK_EQUAL( client1.validateLogin(accessNumber, 4019) , true );

}

// g++ -I /usr/local/boost_1_61_0/ -I ../source/ ../source/Date.cpp ../source/Person.cpp ../source/Account.cpp ../source/ChequingAccount.cpp ../source/SavingsAccount.cpp ../source/Client.cpp  testClient.cpp -o testClient ../boost_serialization/libboost_serialization.a boost_test/libboost_unit_test_framework.a -std=c++11 -Wall