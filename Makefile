
VERSION_ID=$(shell ./gen_version_id.py)
CXXFLAGS= -Wall -pedantic -std=c++11 -I. -Werror -Wextra -DEXT_VER=$(VERSION_ID)
LDFLAGS= -lopencv_core
BINARIES= position_from_camera 

all: $(BINARIES)

position_from_camera: position_from_camera.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	@rm $(BINARIES) 
