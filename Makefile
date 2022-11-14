# Makefile template copied and modified from https://github.com/pantuza/c-project-template


# Source code directory structure
BINDIR := bin
SRCDIR := src
LOGDIR := log
LIBDIR := lib
TESTDIR := test


CC := gcc

STD := -std=gnu99

# Specifies to GCC the required warnings
WARNS := -Wall -Wextra -pedantic # -pedantic warns on language standards

# Flags for compiling
CFLAGS := -I headers/ -O3 $(STD) $(WARNS)

# Debug options
DEBUG := -g3 -DDEBUG=1

# Dependency libraries
LIBS := -lpthread

# Test libraries
TEST_LIBS := -lcunit

# Tests binary file
TEST_BINARY := binary_test_runner


# %.o file names
NAMES := $(notdir $(basename $(wildcard $(SRCDIR)/*.c)))
OBJECTS :=$(patsubst %,$(LIBDIR)/%.o,$(NAMES))


default: all

# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $^ -o $@ $(DEBUG) $(CFLAGS) $(LIBS)


# Rule for link and generate the binary file
all: main.c $(OBJECTS)
	$(CC) -o $(BINDIR)/binary $+ $(DEBUG) $(CFLAGS) $(LIBS)
	@echo "\nBinary file placed at" \
			  "$(BINDIR)/binary\n";
	./$(BINDIR)/binary


# Compile tests and run the test binary
tests: $(TESTDIR)/tests.c $(OBJECTS)
	$(CC) $+ -o $(BINDIR)/$(TEST_BINARY) $(CFLAGS) $(DEBUG) $(LIBS) $(TEST_LIBS)
	@echo " Running tests: ";
	./$(BINDIR)/$(TEST_BINARY)


# Rule for cleaning the project
clean:
	@rm -rvf $(BINDIR)/* $(LIBDIR)/* $(LOGDIR)/*;

.PHONY: clean tests

# Rule for run valgrind tool
valgrind:
	valgrind \
		--track-origins=yes \
		--leak-check=full \
		--leak-resolution=high \
		--log-file=$(LOGDIR)/$@.log \
		$(BINDIR)/binary
	@echo "\nCheck the log file: $(LOGDIR)/$@.log\n"