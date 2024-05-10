#
# Makefile for Binary Search Tree
#
# Homework 3 (fall 2021)
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 


hw3: hw3.o BinarySearchTree.o
	${CXX} -o $@ $^
	
hw3_test1: hw3_test1.o BinarySearchTree.o
	${CXX} -o $@ $^

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -rf hw3 *.o *.dSYM

provide:
	provide comp15 hw3 hw3.cpp BinarySearchTree.cpp BinarySearchTree.h \
	        README Makefile hw3_test1.cpp

