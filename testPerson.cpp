#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Date.h"
#include "Person.h"

TEST_CASE( "Person objects can be created and modified" ) {

    Person p1("John", "Lennon", 9, 10, 1940, 123456789);

    REQUIRE( p1.getFName() == "John" );
    REQUIRE( p1.getLName() == "Lennon" );
    REQUIRE( p1.getBirthDay() == 9 );
    REQUIRE( p1.getBirthMonth() == 10 );
    REQUIRE( p1.getBirthYear() == 1940 );
    REQUIRE( p1.getAge() == 78 );
    REQUIRE( p1.getSSN() == 123456789 );

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
    


}