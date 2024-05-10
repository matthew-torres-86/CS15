#########################################################
#             HOMEWORK 2: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow 
LDFLAGS  = -g3 

# Metrosim rule - you need to fill in the linking command, as well as 
# target rules for Passenger.o, MetroSim.o, and main.o.
# Please use the rules provided below for PassengerQueue.o as an example for
# what to do.
# If you add other classes, you'll have to add their .o files here.
# Don't forget:  the clang++ command must be indented with a TAB character
# and be all on one line.
MetroSim: main.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(LDFLAGS)-o MetroSim main.o MetroSim.o \
	PassengerQueue.o Passenger.o
	

# This rule builds PassengerQueue.o
Passenger.o: Passenger.cpp Passenger.h
	$(CXX) $(CXXFLAGS) -c Passenger.cpp

PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h 
	$(CXX) $(CXXFLAGS) -c PassengerQueue.cpp
	
MetroSim.o: MetroSim.cpp MetroSim.h PassengerQueue.h Passenger.h 
		$(CXX) $(CXXFLAGS) -c MetroSim.cpp
		
Main.o: main.cpp MetroSim.h PassengerQueue.h Passenger.h
		$(CXX) $(CXXFLAGS) -c main.cpp
		

# The below rules are used by unit_test
# This rule will be used by unit_test to build the tests for the 
# PassengerQueue class. 
# please add any other .o files that are needed by Passenger Queue. 
unit_test: unit_test_driver.o PassengerQueue.o PassengerQueue_tests.o \
	Passenger.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o PassengerQueue.o \
	Passenger.o PassengerQueue_tests.o

# This rule builds the unit_test_driver.o file 
# unit_test_driver.cpp will be copied for you when running unit_test.
# This driver will contain main()
unit_test_driver.o: unit_test_driver.cpp
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp

# This rule builds PassengerQueue_tests.o
PassengerQueue_tests.o: PassengerQueue_tests.cpp PassengerQueue.h Passenger.h
	$(CXX) $(CXXFLAGS) -c PassengerQueue_tests.cpp 

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out
