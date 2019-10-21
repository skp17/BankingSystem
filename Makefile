# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = clean

LDIR = ./libs
ODIR = ./build
SDIR = ./source
TDIR = ./test
IDIR = /usr/local/boost_1_61_0/
SRCS := $(wildcard source/*.cpp)
HEADERS := $(wildcard source/*.h)
OBJS := $(patsubst source/%.cpp, build/%.o, $(SRCS))

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I$(IDIR)
LFLAGS = libs/boost_serialization/libboost_serialization.a
# -Llibs/boost_serialization/ -lboost_serialization

MAIN = banksystem

#all: $(MAIN)

bin/$(MAIN): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LFLAGS)

build/%.o: source/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

testDate: Date.o $(TDIR)/testDate.cpp
	$(CXX) $(CXXFLAGS) $(INC_PATH) $^ -o $(TDIR)/$@

testPerson: Date.o Person.o $(TDIR)/testPerson.cpp
	$(CXX) $(CXXFLAGS) $(INC_PATH) $^ -o $(TDIR)/$@

testClient: $(ODIR)/Date.o $(ODIR)/Person.o $(ODIR)/Client.o $(ODIR)/Account.o $(ODIR)/ChequingAccount.o $(ODIR)/SavingsAccount.o $(TDIR)/testClient.cpp
	$(CXX) $(CXXFLAGS) $(INC_PATH) $^ -o $(TDIR)/$@

testAccount: Account.o ChequingAccount.o SavingsAccount.o $(TDIR)/testAccount.cpp
	$(CXX) $(CXXFLAGS) $(INC_PATH) $^ -o $(TDIR)/$@

clean:
	find . -name '*.o' -delete