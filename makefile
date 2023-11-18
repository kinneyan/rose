CC = g++
CFLAGS = -Wall `pkg-config --cflags x11 cairo` `curl-config --cflags`
LIBS = `pkg-config --libs x11 cairo` `curl-config --libs`
SOURCES = $(wildcard source/*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
EXECUTABLE = bin/rose

all:	build $(EXECUTABLE)

$(OBJECTS): source/%.o: source/%.cpp
	$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

build:
	@mkdir -p bin

.PHONY: clean
clean:
	rm -r $(EXECUTABLE) $(OBJECTS) bin
