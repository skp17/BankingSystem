#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Date.h"

SCENARIO( "Ojects of class Date can be created and edited", "[Date]" ) {
    
    GIVEN( "an object with default parameters" ) {
        Date d1;
        
        REQUIRE( d1.getDay() == 1 );
        REQUIRE( d1.getMonth() == 1  );
        REQUIRE( d1.getYear() == 1970);
        d1.printDate();

        WHEN( "date object gets modified" ) {
            d1.setYear(1999).setMonth(12).setDay(25);

            THEN( "objects data members change" ) {
                REQUIRE( d1.getDay() == 25 );
                REQUIRE( d1.getMonth() == 12  );
                REQUIRE( d1.getYear() == 1999);
                d1.printDate();
            }
        }

    GIVEN("object with custom parameters") {
        try {
            Date d2(17,12,1992);

            REQUIRE( d2.getDay() == 17 );
            REQUIRE( d2.getMonth() == 12 );
            REQUIRE( d2.getYear() == 1992 );
            
            WHEN( "object with invalid parameters") {
                Date d3(15,4,30000);
            }
        }
        catch(std::exception const& e) {
            std::cerr << e.what() << '\n';
        }
    }

        WHEN("Object is copied") {
            Date d2(17,12,1992);
            Date d4 = d2;
            REQUIRE( d4.getDay() == 17 );
            REQUIRE( d4.getMonth() == 12 );
            REQUIRE( d4.getYear() == 1992 );
            d4.printDate();
        
            d1.setDate(19,9,2019);
            REQUIRE( d1.getDay() == 19 );
            REQUIRE( d1.getMonth() == 9 );
            REQUIRE( d1.getYear() == 2019 );
            d1.printDate();
        }
    }
}