cmake_minimum_required(VERSION 3.0)

project(test_bank)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE "Debug")

file(GLOB SRCS
    "../source/*.h"
    "../source/*.cpp"
)

include_directories(../source/)
include_directories(/usr/local/boost_1_61_0/)
link_directories(../libs/)

add_executable(testDate ../testDate.cpp ../source/Date.h ../source/Date.cpp)
add_executable(testPerson ../testPerson.cpp ../source/Date.h ../source/Date.cpp 
    ../source/Person.h ../source/Person.cpp)
add_executable(testAccount ../testAccount.cpp ../source/Date.h ../source/Date.cpp 
    ../source/Person.h ../source/Person.cpp  ../source/Account.h ../source/Account.cpp 
    ../source/ChequingAccount.h ../source/ChequingAccount.cpp
    ../source/SavingsAccount.h ../source/SavingsAccount.cpp)
add_executable(testClient ../testClient.cpp ../source/Date.h ../source/Date.cpp 
    ../source/Person.h ../source/Person.cpp  ../source/Account.h ../source/Account.cpp 
    ../source/ChequingAccount.h ../source/ChequingAccount.cpp
    ../source/SavingsAccount.h ../source/SavingsAccount.cpp
    ../source/Client.h ../source/Client.cpp)
add_executable(testBank ../testBank.cpp ../source/Date.h ../source/Date.cpp 
    ../source/Person.h ../source/Person.cpp  ../source/Account.h ../source/Account.cpp 
    ../source/ChequingAccount.h ../source/ChequingAccount.cpp
    ../source/SavingsAccount.h ../source/SavingsAccount.cpp
    ../source/BankManager.h ../source/BankManager.cpp
    ../source/Client.h ../source/Client.cpp)

ADD_LIBRARY(boost_serialization STATIC IMPORTED)
SET_TARGET_PROPERTIES(boost_serialization PROPERTIES 
    IMPORTED_LOCATION ../../libs/libboost_serialization.a)

ADD_LIBRARY(boost_test STATIC IMPORTED)
SET_TARGET_PROPERTIES(boost_test PROPERTIES 
    IMPORTED_LOCATION ../../libs/libboost_unit_test_framework.a)

TARGET_LINK_LIBRARIES(testDate boost_serialization boost_test)
TARGET_LINK_LIBRARIES(testPerson boost_serialization boost_test)
TARGET_LINK_LIBRARIES(testAccount boost_serialization boost_test)
TARGET_LINK_LIBRARIES(testClient boost_serialization boost_test)
TARGET_LINK_LIBRARIES(testBank boost_serialization boost_test)