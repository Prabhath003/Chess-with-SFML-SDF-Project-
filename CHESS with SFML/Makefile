CXX			:= g++
CXX_FLAGS	:= -g -Wall -Wextra -Wno-unused-parameter -std=c++2a -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
TESTBIN	:= testBin
TESTSRC := testFiles

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system 
TESTLIBRARIES := -lgtest -lgtest_main -lgmock -pthread
EXECUTABLE	:= main
TESTTARGET	:= test

SRCS	:= $(wildcard $(SRC)/*.cpp)
OBJS	:= $(patsubst $(SRC)/%.cpp, $(BIN)/%.o, $(SRCS))
TESTSRCS:= $(wildcard $(TESTSRC)/*.cpp)
TESTOBJS:= $(patsubst $(TESTSRC)/%.cpp, $(TESTBIN)/%.o, $(TESTSRCS))
MAINS	:=$(BIN)/main.o
OBJST	:= $(filter-out $(MAINS), $(OBJS))

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

test: $(TESTBIN)/$(TESTTARGET)

$(BIN)/$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $@ $(LIBRARIES)

$(TESTBIN)/$(TESTTARGET):  $(OBJST) $(TESTOBJS)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $(OBJST) $(TESTOBJS) -o $@ $(LIBRARIES) $(TESTLIBRARIES)

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) -c $< -o $@

$(TESTBIN)/%.o: $(TESTSRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) -c $< -o $@

clean:
	$(RM) $(BIN)/*
	$(RM) $(TESTBIN)/*
