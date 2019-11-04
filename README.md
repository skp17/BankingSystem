# BankingSystem

__BankingSystem__ is a command line program that stores client information and allows clients to perform transactions on their accounts.

The project directory is organzed as follows
```bash
.
├── build
├── CMakeLists.txt
├── Doxyfile
├── libs
│   ├── libboost_serialization.a
│   └── libboost_unit_test_framework.a
├── README.md
├── source
│   ├── Account.cpp
│   ├── Account.h
│   ├── BankManager.cpp
│   ├── BankManager.h
│   ├── banksystem.cpp
│   ├── ChequingAccount.cpp
│   ├── ChequingAccount.h
│   ├── Client.cpp
│   ├── Client.h
│   ├── Date.cpp
│   ├── Date.h
│   ├── Person.cpp
│   ├── Person.h
│   ├── SavingsAccount.cpp
│   └── SavingsAccount.h
└── test
    ├── build
    ├── CMakeLists.txt
    ├── testAccount.cpp
    ├── testBank.cpp
    ├── testClient.cpp
    ├── testDate.cpp
    └── testPerson.cpp
```

## Dependencies
* boost c++ libraries

This program uses the Boost Serialization library to store all client information in binary format.

#### `boost::serialization`
```c++
friend class boost::serialization::access;
template<class Archive>
void save(Archive &ar, const uint version) const {
    ar.register_type(static_cast<Client*>(NULL));
    ar & bankName;
    ar & filename;
    ar & clients;
}
```

## Getting Started
In order to compile and run program using cmake, simply follow the instructions below.

Inside CMakeLists.txt, 

Change path to boost directory
```cmake
include_directories(<path to boost directory>)
```

Change path to boost serialization library
```cmake
SET_TARGET_PROPERTIES(boost_serialization PROPERTIES 
    IMPORTED_LOCATION <path to boost serialisation library>)
```
Generate Makefile using cmake,
```bash
$ mkdir build
$ cd build
$ cmake ..
```
Now compile and run
```bash
$ make
$ ./banksystem
```


This program has been tested on Linux Mint.

UML class diagrams were generated using Doxygen and can be viewed here:
[UML Class Diagram](https://skp17.github.io/BankingSystem/
"UML Class Diagram")

View demo

[![View Demo](http://img.youtube.com/vi/nc-04LZ-1fg/0.jpg)](http://www.youtube.com/watch?v=nc-04LZ-1fg)




## License
The MIT License (MIT)

Copyright (c) 2019 Steven Peters



