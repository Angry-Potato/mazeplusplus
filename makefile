SOURCES := $(shell find src -name '*.cpp')
OBJS := $(SOURCES:%.cpp=%.o)
TESTSOURCES := $(filter-out $(wildcard src/main*), $(SOURCES) $(shell find test -name '*.cpp'))
TESTOBJS := $(filter-out $(wildcard src/main*), $(TESTSOURCES:%.cpp=%.o))
DFLAG?=debug

ifeq ($(shell sh -c 'uname -s'),Linux)
	LIBFLAGS=-L. -ltcod_debug -ltcodxx_debug -Wl,-rpath=.
else
	LIBFLAGS=-Llib -ltcod-mingw-debug -static-libgcc -static-libstdc++
endif

ifneq (,$(findstring release,$(MAKECMDGOALS)))
	CFLAGS=-O2 -s
else
	CFLAGS=-g
endif

help :
	@echo "Welcome to Mazeplusplus Makefile!"
	@echo "Commands available are:"
	@echo "make debug		# Compiles mazeplusplus to ./bin/mazepp, runs unit tests, then runs a clean"
	@echo "make release		# Compiles mazeplusplus to ./bin/mazepp with compiler flags to optimise for executable size + speed, runs unit tests, then runs a clean"
	@echo "make mazepp		# Compiles mazeplusplus to ./bin/mazepp, then runs unit tests"
	@echo "make clean		# Removes all *.o files in the project"
	@echo "make unit_test		# Compiles the test executable to ./bin/test_mazepp, then runs unit tests"
	@echo "make dockermazepp	# Runs compilation and unit tests in a container, then copies executables out to ./bin/"
	@echo "make dockerclean	# Removes the mazepp container"
	@echo "make dockercp		# Copies executables out from the mazepp container, and into ./bin"
	@echo "make dockerrun		# Runs given target in mazepp container (defaults to debug)"
	@echo "make dockerbuild	# Builds the mazepp container"

debug : mazepp clean

release : mazepp clean

mazepp : $(OBJS) unit_test
	g++ $(OBJS) -o bin/mazepp -Wall $(LIBFLAGS) $(CFLAGS)

clean :
	rm -f $(OBJS) $(TESTOBJS)

%.o : %.cpp %.h
	g++ $< -c -o $@ -Iinclude -Wall $(CFLAGS)

unit_test : test
	./bin/test_mazepp -fc

test : $(TESTOBJS)
	g++ $(TESTOBJS) -o bin/test_mazepp -Wall $(LIBFLAGS) $(CFLAGS)

dockermazepp : dockercp
	make dockerclean

dockerclean :
	docker rm mazegamebuilder

dockercp : dockerrun
	docker cp mazegamebuilder:/mazegame/bin/mazepp ./bin && docker cp mazegamebuilder:/mazegame/bin/test_mazepp ./bin

dockerrun : dockerbuild
	docker run --name mazegamebuilder imazegamebuilder make clean $(DFLAG)

dockerbuild :
	docker build -t imazegamebuilder .
