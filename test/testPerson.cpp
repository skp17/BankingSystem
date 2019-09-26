#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Date.h"
#include "Person.h"

TEST_CASE( "Person objects can be created and modified" ) {

    Person p1("John", "Lennon", 9, 10, 1940, 123456789);
    p1.setAddress("9 St-Catherine Est").setTelephone("514-777-7777");
    p1.setEmail("jlennon@gmail.com");

    REQUIRE( p1.getFName() == "John" );
    REQUIRE( p1.getLName() == "Lennon" );
    REQUIRE( p1.getBirthDay() == 9 );
    REQUIRE( p1.getBirthMonth() == 10 );
    REQUIRE( p1.getBirthYear() == 1940 );
    REQUIRE( p1.getAge() == 78 );
    REQUIRE( p1.getSSN() == 123456789 );
    REQUIRE( p1.getAddress() == "9 St-Catherine Est");
    REQUIRE( p1.getTelephone() == "514-777-7777");
    REQUIRE( p1.getEmail() == "jlennon@gmail.com");
    
    SECTION( "Objects of class Person can be copied" ) {
        Person p2 = p1;

        REQUIRE( p1.getFName() == "John");
        REQUIRE( p1.getLName() == "Lennon");
        REQUIRE( p1.getBirthDay() == 9 );
        REQUIRE( p1.getBirthMonth() == 10 );
        REQUIRE( p1.getBirthYear() == 1940 );
        REQUIRE( p1.getAge() == 78 );
        REQUIRE( p1.getSSN() == 123456789 );
        
    }
    
    SECTION( "Objects of class Person can be modified" ) {
        Date birthdate(1,11,1961);
        Person someone("Reed", "Richards", birthdate, 123789456);

        REQUIRE( someone.getFName() == "Reed" );
        REQUIRE( someone.getLName() == "Richards" );
        REQUIRE( someone.getAge() == 57 );
        REQUIRE( someone.getBirthDay() == 1 );
        REQUIRE( someone.getBirthMonth() == 11 );
        REQUIRE( someone.getBirthYear() == 1961 );
        REQUIRE( someone.getSSN() == 123789456 );

        someone.setName("Michael", "Scott");

        REQUIRE( someone.getFName() == "Michael" );
        REQUIRE( someone.getLName() == "Scott" );
    }

}