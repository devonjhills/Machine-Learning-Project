CC=g++
CFLAGS=-c
CPP=-std=c++0x
SOURCES=main.cpp connect4.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=con4

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CPP) $(OBJECTS) $(DEPS) -o $@ -I/Applications/MATLAB.app/extern/include/ -L/Applications/MATLAB.app/bin/maci64 -leng -lmx

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I/Applications/MATLAB.app/extern/include/

clean:
	-rm *.o $(OBJECTS) con4
