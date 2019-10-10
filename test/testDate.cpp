#include "Date.h"
#define BOOST_TEST_MODULE Date test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( my_test )
{
    Date date(10,10,2019);

    BOOST_CHECK( date.getDay() == 10 );
    BOOST_CHECK( date.getMonth() == 10 );
    BOOST_CHECK( date.getYear() == 2018 );

}
