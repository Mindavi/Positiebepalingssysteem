cmake_minimum_required(VERSION 3.1)
project(plotter)
add_executable(plotter plotter.cpp)
include_directories("${PROJECT_BINARY_DIR}")
target_link_libraries(plotter opencv_core opencv_highgui opencv_imgproc)
target_compile_options(plotter PRIVATE -Wall -pedantic -Wextra)
set_target_properties (plotter PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS FALSE
)
