CC = g++

CFLAGS = -I/usr/include/GL -g -O2 -std=c++11 -Wall
LDFLAGS = -lGL -lGLUT -lSOIL

SOURCES = Main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = bullet

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
