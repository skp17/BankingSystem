# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = clean

DEPS = $(wildcard *.h)
SRCS :=  $(wildcard *.cpp)
OBJS := $(SRCS:$.cpp=o)
ODIR = ./build
TDIR = ./test
INC_PATH := -I. -I $(ODIR)

CXX = g++
CXXFLAGS = -std=c++11 -Wall
LINKERFLAG = -lm

build: $(SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) -c *.cpp
	mkdir -p $(ODIR)
	mv *.o $(ODIR)

BankingSystem: Date.o Person.o BankingSystem.o
	$(CXX) $(CXXFLAGS) $(INC_PATH) $^ -o $@

Date: Date.o
	$(CXX) $(CXXFLAGS) $(INC_PATH) $^ -o $@

Client: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC_PATH) $^ -o $@

Account: Account.o ChequingAccount.o SavingsAccount.o
	$(CXX) $(CXXFLAGS) $(INC_PATH) $^ -o $@

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