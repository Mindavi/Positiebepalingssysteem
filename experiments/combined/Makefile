CXX = clang++
CXXFLAGS = -Wall -Wextra -c
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_video -lopencv_imgproc
LDFLAGS_PLOTTER = -lopencv_core -lopencv_imgproc -lopencv_highgui
SOURCES = combined.cpp
SOURCES_PLOTTER = coordinateplotter.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_PLOTTER = $(SOURCES_PLOTTER:.cpp=.o)

BINARY = combined.exe 
BINARY_PLOTTER = plotter.exe

.PHONY: all clean dist-clean

all: $(BINARY) $(BINARY_PLOTTER)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY_PLOTTER): $(OBJECTS_PLOTTER)
	$(CXX) -o $@ $^ $(LDFLAGS_PLOTTER)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf *.o

dist-clean: clean
	@rm -rf *.exe
