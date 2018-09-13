
CC = g++
LD = ld

WARNINGS = -Wall -Wextra
DEBUG = -g

TESTS = tests/tests.cpp
APP = src/app.cpp
OBJS = src/core/*.c lib/libglfw3.a lib/libassimp.so src/core/*.cpp src/game/*.cpp

INCS = -I/usr/include/
LIB_PATH = -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -L./lib -L.
LIBS = -lX11 -lGL -lglfw -lXrandr -lXi -lXxf86vm -lpthread -ldl -lXcursor -lXinerama -lstdc++ -lassimp

FLAGS = $(WARNINGS) $(DEBUG) -std=c++11
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
	$(CC) $(FLAGS) -o bin/app -DDEBUG $(APP) $(OBJS) $(LDLIBS)

app: $(APP) $(OBJS)
	@echo "Building target" $@ "..." 
	$(CC) $(FLAGS) -o bin/app -DNDEBUG $(APP) $(OBJS) $(LDLIBS)

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