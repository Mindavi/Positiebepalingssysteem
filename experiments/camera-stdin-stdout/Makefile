CXX = g++

CXXFLAGS = -Wall -Wextra -c
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -I.
SOURCES = read-video-stdin.cpp ImageReader.cpp
SOURCES_EDIT = read-edit.cpp ImageReaderEncode.cpp ImageReader.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_EDIT = $(SOURCES_EDIT:.cpp=.o)

BINARY = read-and-view-video.exe
BINARY_EDIT = read-and-view-with-edit.exe
ALL_BINARIES = $(BINARY) $(BINARY_EDIT)

.PHONY: all clean

all: $(ALL_BINARIES)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY_EDIT): $(OBJECTS_EDIT)
	$(CXX) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf $(ALL_BINARIES) *.o
