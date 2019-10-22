cmake_minimum_required(VERSION 3.0)

project(banksystem)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE "Release")

file(GLOB SRCS
    "source/*.h"
    "source/*.cpp"
)

include_directories(source/)
include_directories(/usr/local/boost_1_61_0/)
link_directories(libs/)

add_executable(banksystem ${SRCS})

ADD_LIBRARY(boost_serialization STATIC IMPORTED)
SET_TARGET_PROPERTIES(boost_serialization PROPERTIES 
    IMPORTED_LOCATION ../libs/libboost_serialization.a)
TARGET_LINK_LIBRARIES(banksystem boost_serialization)
