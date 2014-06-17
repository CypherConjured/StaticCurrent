# boilerplate settings...
SHELL = /bin/bash
CXX = g++ -c
CXXFLAGS += -std=c++11 -I/usr/include -g -Wall -Wextra
LIBS = -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -lsfml-audio
LD = g++
LDFLAGS = -rdynamic -fno-stack-protector


# all library code is in src/

# Project name
PROJECT = WBSC

# Client Files and folders
SRCS = $(shell find src/ -name '*.cpp')
DIRS = $(shell find src/ -type d | sed 's/src/./g' ) 
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SRCS))

# Targets
$(PROJECT): buildrepo $(OBJS)
	$(LD) $(OBJS) $(LIBS) -o $@

obj/%.o: src/%.cpp
	$(LD) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(PROJECT) obj -Rf

buildrepo:
	mkdir -p obj
	for dir in $(DIRS); do mkdir -p obj/$$dir; done
