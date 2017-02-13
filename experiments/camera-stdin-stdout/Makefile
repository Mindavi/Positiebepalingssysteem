CXX = g++

CXXFLAGS = -Wall -Wextra -c
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -I.
SOURCES = read-video-stdin.cpp ImageReader.cpp
SOURCES_EDIT = read-edit.cpp ImageReaderEncode.cpp ImageReader.cpp
SOURCES_BG = ImageReader.cpp BgSubtract.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_EDIT = $(SOURCES_EDIT:.cpp=.o)
OBJECTS_BG = $(SOURCES_BG:.cpp=.o)

LDFLAGS_BG = -lopencv_core -lopencv_imgcodecs -lopencv_video

BINARY = read-and-view-video.exe
BINARY_EDIT = read-and-view-with-edit.exe
BINARY_BG = bg-subtract.exe

ALL_BINARIES = $(BINARY) $(BINARY_EDIT) $(BINARY_BG)

.PHONY: all clean

all: $(ALL_BINARIES)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY_EDIT): $(OBJECTS_EDIT)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY_BG): $(OBJECTS_BG)
	$(CXX) -o $@ $^ $(LDFLAGS_BG)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf $(ALL_BINARIES) *.o
