#########################################################
#                   HOMEWORK 1: LISTS                   #
# by C.R. Calabrese, Jan-Feb 2021                       #
#########################################################

CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow 
LDFLAGS  = -g3 

default: unit_test

# this rule is necessary for Matt Russell's unit testing framework.
# more information on how to use this testing framework can be
# found in the lab 1 materials.
unit_test: unit_test_driver.cpp CharList_tests.cpp \
CharArrayList.cpp CharLinkedList.cpp CharArrayList.h CharLinkedList.h
	$(CXX) $(CXXFLAGS) unit_test_driver.cpp CharList_tests.cpp \
	CharArrayList.cpp CharLinkedList.cpp

# remove executables and object code from the current folder -- the 
# executable created by unit_test is called a.out
clean: 
	rm *.o a.out

# submit the homework
provide:
	provide comp15 hw1 \
	CharLinkedList.cpp CharLinkedList.h \
	CharArrayList.cpp  CharArrayList.h \
	CharList_tests.cpp README Makefile
