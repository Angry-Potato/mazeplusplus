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

debug : mazepp clean

release : mazepp

mazepp : $(OBJS) unit_test
	g++ $(OBJS) -o bin/mazepp -Wall $(LIBFLAGS) $(CFLAGS)

clean :
	rm -f $(OBJS) $(TESTOBJS)

%.o : %.cpp %.h
	g++ $< -c -o $@ -Iinclude -Wall $(CFLAGS)

unit_test : test
	./bin/test_mazepp

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
