CC=gcc
CFLAGS=-Wall
INCLUDES=-I/usr/local/include
LDFLAGS=-L/usr/local/lib/ -lfcgi

.SUFFIXES:
	
MODULES=aux
SOURCES=$(MODULES:=.c)
OBJECTS=$(MODULES:=.o)
HEADERS=$(MODULES:=.h)

$(MODULES): $(SOURCES) $(HEADERS)
	$(CC) -c $(CFLAGS) $(INCLUDES) $@.c -o $@.o

EXECUTABLE=fcgit

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $@.c $(OBJECTS) $(INCLUDES) $(LDFLAGS) 
	# echo $(OBJECTS)

test: $(OBJECTS)
	echo $(MODULES)
	echo $(SOURCES)
	echo $(OBJECTS)



