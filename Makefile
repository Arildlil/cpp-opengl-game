
CC = gcc
LD = ld

WARNINGS = -Wall -Wextra
DEBUG = -g

TESTS = tests/tests.cpp
APP = src/app.cpp
OBJS = lib/libglfw3.a src/*.c 

INCS = -I/usr/include/
LIB_PATH = -L/usr/lib/
LIBS = -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lstdc++

FLAGS = $(WARNINGS) $(DEBUG)
LDLIBS = $(LIB_PATH) $(LIBS)

.PHONY: all clean install debug run lrun test vtest

all: app

# Compile all .c files into .o files.
# .c.o: 
#	@echo "Compiling" $< "..."
#	$(CC) $(CFLAGS) -c $<

tests: $(TESTS) $(OBJS) 
	@echo "Building target" $@ "..."
	$(CC) $(FLAGS) $(TESTS) $(OBJS) $(LDLIBS) -o bin/$@ 

debug: $(APP) $(OBJS)
	@echo "Building target" $@ "in DEBUG mode..." 
	$(CC) $(FLAGS) -DDEBUG $(APP) $(OBJS) $(LDLIBS) -o bin/app

app: $(APP) $(OBJS)
	@echo "Building target" $@ "..." 
	$(CC) $(FLAGS) $(APP) $(OBJS) $(LDLIBS) -o bin/$@

test: bin/tests
	@echo "Running test suite with all tests..."
	./bin/tests

vtest: bin/tests
	@echo "(Valgrind) Running test suite with all test..."
	valgrind ./bin/tests -v --leak-check=full

run: bin/app
	./bin/app

lrun: bin/app
	make run > output.log; cat output.log

# Clean up!
clean:
	rm -f *.o bin/app bin/tests



# $? 	list of dependencies changed more recently than current target.
# $@	name of current target.
# $<	name of current dependency.
# $*	name of current dependency without extension.