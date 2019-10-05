#include "Date.h"
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;
using boost::serialization::make_binary_object;
using boost::serialization::binary_object;

int main() {

    Date orig_date(17, 12, 1992);

    // make an archive
    ofstream ofs("date.dat", ofstream::binary);
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << make_binary_object(&orig_date, sizeof(Date));
    ofs.close();

    Date new_date;

    // open archive
    ifstream ifs("date.dat", ifstream::binary);
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);

    // restore date from the archive
    ia >> make_binary_object(&new_date, sizeof(Date));

    new_date.printDate();

    ifs.close();

    return 0;
}