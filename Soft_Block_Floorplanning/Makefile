CC=g++
LDFLAGS=-std=c++11 -O3 -lm
SOURCES=./src/*.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=./bin/floorplanner
INCLUDES=*.h

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
	rm -rf *.png 
	rm -rf *.gp 
	
