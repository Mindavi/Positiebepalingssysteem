CXX = clang++
CXXFLAGS = -Wall -Wextra -c
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_video -lopencv_imgproc -lopencv_features2d -lpthread
LDFLAGS_SHOW = -lopencv_core -lopencv_imgproc -lopencv_highgui
SOURCES = combined.cpp
SOURCES_SHOW = show.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_SHOW = $(SOURCES_SHOW:.cpp=.o)

BINARY = combined.exe 
BINARY_SHOW = show.exe

.PHONY: all clean dist-clean

all: $(BINARY) $(BINARY_SHOW)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY_SHOW): $(OBJECTS_SHOW)
	$(CXX) -o $@ $^ $(LDFLAGS_SHOW)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf *.o

dist-clean: clean
	@rm -rf *.exe
