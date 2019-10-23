# BankingSystem

__BankingSystem__ is a command line program that stores client information and allows clients to perform transactions on their accounts.

## Dependencies
* boost c++ libraries

This program uses the Boost Serialization library to store all client information in binary format.

#### `boost::serialization`
``` c++
friend class boost::serialization::access;
template<class Archive>
void save(Archive &ar, const uint version) const {
    ar.register_type(static_cast<Client*>(NULL));
    ar & bankName;
    ar & filename;
    ar & clients;
}
```

This program has been tested on Linux Mint.

UML class diagrams were generated using Doxygen and can be viewed here:
[UML Class Diagram](https://skp17.github.io/BankingSystem/
"UML Class Diagram")


This program was written by Steven Peters and is free to use by all.

