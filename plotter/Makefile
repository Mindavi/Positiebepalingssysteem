CXX = clang++
CXXFLAGS = -Wall -Wextra -c
LDFLAGS_PLOTTER = -lopencv_core -lopencv_imgproc -lopencv_highgui
SOURCES_PLOTTER = coordinateplotter.cpp
OBJECTS_PLOTTER = $(SOURCES_PLOTTER:.cpp=.o)

BINARY_PLOTTER = plotter.exe

.PHONY: all clean dist-clean

all: $(BINARY_PLOTTER)

$(BINARY_PLOTTER): $(OBJECTS_PLOTTER)
	$(CXX) -o $@ $^ $(LDFLAGS_PLOTTER)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf *.o

dist-clean: clean
	@rm -rf *.exe
