CXX = g++

CXXFLAGS = -Wall -Wextra -c

LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -I.
LDFLAGS_BG = -lopencv_core -lopencv_imgcodecs -lopencv_video -I.
LDFLAGS_ER = -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -I.
LDFLAGS_DI = $(LDFLAGS_ER)
LDFLAGS_BL = $(LDFLAGS_ER)
LDFLAGS_TH = $(LDFLAGS_ER)

SOURCES = Log.cpp read-video-stdin.cpp ImageReader.cpp print_image.cpp
SOURCES_EDIT = Log.cpp read-edit.cpp ImageReaderEncode.cpp ImageReader.cpp print_image.cpp
SOURCES_BG = ImageReader.cpp BgSubtract.cpp print_image.cpp Log.cpp
SOURCES_IMAGEPROC_COMMON = ImageReader.cpp print_image.cpp Log.cpp
SOURCES_ER = $(SOURCES_IMAGEPROC_COMMON) erode.cpp
SOURCES_DI = $(SOURCES_IMAGEPROC_COMMON) dilate.cpp
SOURCES_BL = $(SOURCES_IMAGEPROC_COMMON) blur.cpp
SOURCES_TH = $(SOURCES_IMAGEPROC_COMMON) threshold.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_EDIT = $(SOURCES_EDIT:.cpp=.o)
OBJECTS_BG = $(SOURCES_BG:.cpp=.o)
OBJECTS_ER = $(SOURCES_ER:.cpp=.o)
OBJECTS_DI = $(SOURCES_DI:.cpp=.o)
OBJECTS_BL = $(SOURCES_BL:.cpp=.o)
OBJECTS_TH = $(SOURCES_TH:.cpp=.o)

BINARY = read-and-view-video.exe
BINARY_EDIT = read-and-view-with-edit.exe
BINARY_BG = bg-subtract.exe
BINARY_ER = erode.exe
BINARY_DI = dilate.exe
BINARY_BL = blur.exe
BINARY_TH = threshold.exe

ALL_BINARIES = $(BINARY) $(BINARY_EDIT) $(BINARY_BG) $(BINARY_ER) $(BINARY_DI) $(BINARY_BL) $(BINARY_TH)

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

$(BINARY_DI): $(OBJECTS_DI)
	$(CXX) -o $@ $^ $(LDFLAGS_DI)

$(BINARY_BL): $(OBJECTS_BL)
	$(CXX) -o $@ $^ $(LDFLAGS_BL)

$(BINARY_TH): $(OBJECTS_TH)
	$(CXX) -o $@ $^ $(LDFLAGS_TH)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf *.o

dist-clean: clean
	@rm -rf *.exe
