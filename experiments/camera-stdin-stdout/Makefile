CXX = g++

CXXFLAGS = -Wall -Wextra -c
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -I.
BINARY = read-and-view-video.exe
SOURCES = read-video-stdin.cpp ImageReader.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf $(BINARY) *.o
