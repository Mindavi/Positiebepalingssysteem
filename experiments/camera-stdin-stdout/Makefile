CXX = g++

CXXFLAGS = -Wall -Wextra -c
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -I.
BINARY = read-and-view-video.exe
BINARY_EDIT = read-and-view-with-edit.exe
SOURCES = read-video-stdin.cpp ImageReader.cpp
SOURCES_EDIT = read-edit.cpp ImageReaderEncode.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_EDIT = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(BINARY) $(BINARY_EDIT)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY_EDIT): $(OBJECTS_EDIT)
	$(CXX) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf $(BINARY) *.o
