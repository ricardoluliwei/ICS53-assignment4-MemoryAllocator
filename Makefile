# University of California, Irvine
# ICS 53
# Author: Liwei Lu
# This Makefile is able to compile all c file in the src folder
# and put the ELF file in the build folder.

# Use gcc as a compiler
CC=gcc
CFLAGS=-g -fprofile-arcs -ftest-coverage
SOURCES := $(wildcard *.c)
REMOVE := $(patsubst %.c, %, $(SOURCES))
EXECUTABLES := $(patsubst %.c, %, $(SOURCES))


.PHONY: all clean 
.PRECIOUS: build/% 

all: $(EXECUTABLES)
	@echo Done!

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -rf $(REMOVE)
	@rm -rf $(wildcard *.gcda) $(wildcard *.gcno) $(wildcard core*)
	@echo Clean All!

clean-%:
	@rm -rf $*.gcda $*.gcno
	@echo Clean 
