#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Date.h"

TEST_CASE("Testing objects of class Date", "[Date]") {
    
    Date d1;
    Date d2(17,12,1992);

    SECTION("Testing default constructor") {
        REQUIRE( d1.getDay() == 1 );
        REQUIRE( d1.getMonth() == 1  );
        REQUIRE( d1.getYear() == 1970);
        d1.printDate();
    }

    SECTION("Testing overloaded constructor") {
        REQUIRE( d2.getDay() == 17 );
        REQUIRE( d2.getMonth() == 12 );
        REQUIRE( d2.getYear() == 1992 );
        Date d3(35,14,3000);
        REQUIRE( d3.getDay() == 1 );
        REQUIRE( d3.getMonth() == 1 );
        REQUIRE( d3.getYear() == 1970 );
    }

    SECTION("Testing copy constructor") {
        Date d4 = d2;
        REQUIRE( d4.getDay() == 17 );
        REQUIRE( d4.getMonth() == 12 );
        REQUIRE( d4.getYear() == 1992 );
        d4.printDate();
    }

    SECTION("Testing set function") {
        d1.setDate(19,9,2019);
        REQUIRE( d1.getDay() == 19 );
        REQUIRE( d1.getMonth() == 9 );
        REQUIRE( d1.getYear() == 2019 );
        d1.printDate();
        
        d1.setDay(25);
        d1.setMonth(12);
        d1.setYear(1000);
        d1.printDate();
    }

    

}