CXX = clang++
CXXFLAGS = -Wall -Wextra -c
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_video -lopencv_imgproc
SOURCES = position.cpp
OBJECTS = $(SOURCES:.cpp=.o)

BINARY = position.exe 

.PHONY: all clean dist-clean

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	@rm -rf *.o

dist-clean: clean
	@rm -rf *.exe
