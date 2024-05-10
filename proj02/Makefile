#
# Makefile for Six Degrees
#
# Project 2 (fall 2020)
#
# Provides for easier command entries from user for compilation, etc.
# 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 
INCLUDES = $(shell echo *.h)

SixDegrees: main.o SixDegrees.o CollabGraph.o Artist.o
	${CXX} -o $@ $^

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -rf SixDegrees *.o *.dSYM


providephase1:
	provide comp15 proj2phase1 SixDegrees.cpp SixDegrees.h \
	main.cpp README Makefile testgraph.txt CollabGraph.cpp CollabGraph.h 
	# ADD TESTING FILES HERE

providephase2:
	provide comp15 proj2phase2 SixDegrees.cpp SixDegrees.h \
			main.cpp README Makefile CollabGraph.cpp CollabGraph.h \
			testgraph.txt commands.txt
