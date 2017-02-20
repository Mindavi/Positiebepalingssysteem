CXX = g++

CXXFLAGS = -Wall -Wextra -c

LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -I.
LDFLAGS_BG = -lopencv_core -lopencv_imgcodecs -lopencv_video -I.
LDFLAGS_ER = -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -I.

SOURCES = Log.cpp read-video-stdin.cpp ImageReader.cpp print_image.cpp
SOURCES_EDIT = Log.cpp read-edit.cpp ImageReaderEncode.cpp ImageReader.cpp print_image.cpp
SOURCES_BG = ImageReader.cpp BgSubtract.cpp print_image.cpp Log.cpp
SOURCES_ER = ImageReader.cpp print_image.cpp erode.cpp Log.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_EDIT = $(SOURCES_EDIT:.cpp=.o)
OBJECTS_BG = $(SOURCES_BG:.cpp=.o)
OBJECTS_ER = $(SOURCES_ER:.cpp=.o)

BINARY = read-and-view-video.exe
BINARY_EDIT = read-and-view-with-edit.exe
BINARY_BG = bg-subtract.exe
BINARY_ER = erode.exe

ALL_BINARIES = $(BINARY) $(BINARY_EDIT) $(BINARY_BG) $(BINARY_ER)

.PHONY: all clean dist-clean

all: $(ALL_BINARIES)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY_EDIT): $(OBJECTS_EDIT)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY_BG): $(OBJECTS_BG)
	$(CXX) -o $@ $^ $(LDFLAGS_BG)

$(BINARY_ER): $(OBJECTS_ER)
	$(CXX) -o $@ $^ $(LDFLAGS_ER)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf *.o

dist-clean: clean
	@rm -rf *.exe
