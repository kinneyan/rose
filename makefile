CC = g++
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
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
