CXX = g++

CXXFLAGS = -Wall -Wextra -c -Ilib

LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs

SOURCES = lib/Log.cpp view.cpp lib/ImageReader.cpp lib/print_image.cpp

OBJECTS = $(SOURCES:.cpp=.o)

BINARY = view.exe

ALL_BINARIES = $(BINARY)

.PHONY: all clean dist-clean

all: $(ALL_BINARIES)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf *.o lib/*.o

dist-clean: clean
	@rm -rf *.exe
