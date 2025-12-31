CC=g++
LDFLAGS=-std=c++17 -O3
SOURCES=./src/*.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=./bin/CGR
INCLUDES=./src/*.h

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE)
	rm *.bmp 
	rm *.rpt 

