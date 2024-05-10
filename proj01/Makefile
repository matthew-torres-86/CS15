###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  YOUR NAME HERE

CXX      = clang++
CXXFLAGS = -g -Wall -Wextra -std=c++11
LDFLAGS  = -g

## This runs clang++ on all of the up to date .o files defined below to form 
## an excecutable for RPNCalc
CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o
	${CXX} ${LDFLAGS} -o RPNCalc  main.o RPNCalc.o DatumStack.o Datum.o

## This runs clang++ on all of the up to date .o files defined below to form 
## an excecutable for just parser.cpp (NOTE: Uncomment main)
Parser: parser.o DatumStack.o Datum.o
	${CXX} ${LDFLAGS} -o Parser Datum.o DatumStack.o parser.o
	
## This rule forms main.o, lists all its dependencies and establishes its 
## recipe
main.o: main.cpp Datum.h DatumStack.h RPNCalc.h
	${CXX} ${CXXFLAGS} -c main.cpp
	
## This rule forms RPNCalc.o, lists all its dependencies and establishes its 
## recipe
RPNCalc.o: RPNCalc.cpp Datum.h DatumStack.h RPNCalc.h
	${CXX} ${CXXFLAGS} -c RPNCalc.cpp
	
## This rule forms DatumStack.o, lists all its dependencies and establishes its 
## recipe
DatumStack.o: DatumStack.cpp Datum.h DatumStack.h
	${CXX} ${CXXFLAGS} -c DatumStack.cpp

## This rule forms parser.o, lists all its dependencies and establishes its 
## recipe
parser.o: parser.cpp Datum.h DatumStack.h 
	${CXX} ${CXXFLAGS} -c parser.cpp 


## The following rules are needed for the Unit test framework
unit_test: unit_test_driver.o DatumStack.o DatumStack_tests.o Datum.o 
	$(CXX) $(CXXFLAGS) unit_test_driver.o DatumStack.o \
	DatumStack_tests.o Datum.o

unit_test_driver.o: unit_test_driver.cpp
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp

DatumStack_tests.o: DatumStack_tests.cpp Datum.h DatumStack.h
	$(CXX) $(CXXFLAGS) -c DatumStack_tests.cpp
##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

clean: 
	rm DatumStack.o DatumStack_tests.o RPNCalc.o main.o