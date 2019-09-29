# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

CXX = g++
CXXFLAGS = -I. -std=c++11 -Wall -MMD -MD
LINKERFLAG = -lm
DEPS = $(wildcard *.h)
SRCS :=  $(wildcard *.cpp)
OBJS := $(SRCS:$.cpp=o)
ODIR = ./build
TDIR = ./test

-include ${DEPS}

%.o: %.cpp %.h
	${CXX} ${CXXFLAGS} -c $< -o ${ODIR}/$@

build: $(OBJS)

BankingSystem: ${ODIR}/Date.o ${ODIR}/Person.o ${ODIR}/BankingSystem.o
	${CXX} ${CXXFLAGS} $^ -o $@

Date: ${OBJS}
	${CXX} ${CXXFLAGS} -c $< -o $@

${ODIR}/Person.o: Person.cpp Person.h
	${CXX} ${CXXFLAGS} $< -c -o $@

${ODIR}/Account.o: Account.cpp Account.h
	${CXX} ${CXXFLAGS} $< -c -o $@

${ODIR}/ChequingAccount.o: ChequingAccount.cpp ChequingAccount.h
	${CXX} ${CXXFLAGS} $< -c -o $@

${ODIR}/SavingsAccount.o: SavingsAccount.cpp SavingsAccount.h
	${CXX} ${CXXFLAGS} $< -c -o $@

${ODIR}/BankManager.o: ${ODIR}/Date.o ${ODIR}/Person.o BankingManager.cpp
	${CXX} ${CXXFLAGS} $^ -c -o $@

testDate: ${ODIR}/Date.o ${TDIR}/testDate.cpp
	${CXX} ${CXXFLAGS} $^ -o ${TDIR}/$@

testPerson: ${ODIR}/Date.o ${ODIR}/Person.o ${TDIR}/testPerson.cpp
	${CXX} ${CXXFLAGS} $^ -o ${TDIR}/$@

testClient: ${ODIR}/Date.o ${ODIR}/Person.o ${ODIR}/Client.o ${ODIR}/Account.o ${ODIR}/ChequingAccount.o ${ODIR}/SavingsAccount.o ${TDIR}/testClient.cpp
	${CXX} ${CXXFLAGS} $^ -o ${TDIR}/$@

testAccount: ${ODIR}/Account.o ${ODIR}/ChequingAccount.o ${ODIR}/SavingsAccount.o ${TDIR}/testAccount.cpp
	${CXX} ${CXXFLAGS} $^ -o ${TDIR}/$@

clean:
	rm ${ODIR}/*.o