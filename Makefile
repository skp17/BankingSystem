# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

CXX = g++
CXXFLAGS = -std=c++11 -Wall
LINKERFLAG = -lm
DEPS = $(wildcard *.h)
SRCS := Date.cpp Person.cpp BankingSystem.cpp
OBJS := $(SRCS:$.cpp=o)
ODIR = objects

all: BankingSystem

BankingSystem: ${ODIR}/Date.o ${ODIR}/Person.o ${ODIR}/BankingSystem.o
	${CXX} ${CXXFLAGS} $^ -o $@

${ODIR}/Date.o: Date.cpp
	${CXX} ${CXXFLAGS} $^ -c -o $@

${ODIR}/Person.o: ${ODIR}/Date.o Person.cpp
	${CXX} ${CXXFLAGS} $^ -c -o $@

${ODIR}/BankingSystem.o: ${ODIR}/Date.o ${ODIR}/Person.o BankingSystem.cpp
	${CXX} ${CXXFLAGS} $^ -c -o $@

%.cpp: %.h

testDate: ${ODIR}/Date.o
	${CXX} ${CXXFLAGS} $^ $@

testPerson: ${ODIR}Date.o ${ODIR}Person.o
	${CXX} ${CXXFLAGS} $^ $@

Date.cpp: Date.h

Person.cpp: Person.h

clean:
	rm ${ODIR}/*.o




