# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

C_COMPILER=gcc
ifeq ($(shell uname -s), Darwin)
C_COMPILER=clang
endif

GCCFLAGS = -g -Wall -Wfatal-errors
ALL = identifier
GCC = gcc



UNITY_ROOT=../Unity

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

TARGET_BASE1=all_tests
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
SRC_FILES1=\
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  src/identifier_mainless.c \
  test/identifierTest.c \
  test/test_runners/identifierTest_Runner.c 
INC_DIRS=-Isrc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src
SYMBOLS=

all: clean compile run valgrind cppcheck cov runcov

compile:
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)
	

run:
	- ./$(TARGET1) -v

clean:
	$(CLEANUP) $(TARGET1)
	rm -fr $(ALL) *.o cov* *.dSYM *.gcda *.gcno *.gcov cachegrind* callgrind*

valgrind:
	#Memcheck
	- valgrind --leak-check=full ./$(TARGET1) -v
	
	#Cachegrind
	#- valgrind --tool=cachegrind ./$(TARGET1) -v

	#Callgrind
	#- valgrind --tool=callgrind ./$(TARGET1) -v

	#Massif
	#- valgrind --tool=massif ./$(TARGET1) -v

	#Helgrind
	#- valgrind --tool=helgrind ./$(TARGET1) -v

cppcheck:
	- cppcheck ./identifierTest -v


identifier: ./src/identifier.c
	$(GCC) $(GCCFLAGS) -o $@ $@.c 

cov: ./src/identifier.c
	$(GCC) $(GCCFLAGS) -fprofile-arcs -ftest-coverage -o $@ ./src/identifier.c

runcov: 
	- echo a | ./cov;
	- echo ab | ./cov;
	- echo abc | ./cov;
	- echo abcd | ./cov;
	- echo abcde | ./cov;
	- echo A123e | ./cov;
	- echo 123e | ./cov;
	- echo 1 | ./cov;
	- echo a23elKz | ./cov;
	- echo a23%el | ./cov;
	- echo 234 | ./cov;
	- gcov -b identifier.c
	

ci: CFLAGS += -Werror
ci: compile
