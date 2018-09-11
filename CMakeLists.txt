cmake_minimum_required(VERSION 3.1)
project(position)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(position position.cpp)
include_directories("${PROJECT_BINARY_DIR}")
target_link_libraries(position opencv_core opencv_highgui opencv_videoio opencv_video opencv_imgproc)
execute_process(COMMAND git describe --long --tags --dirty OUTPUT_VARIABLE VERSION_ID)
target_compile_definitions(position PRIVATE "EXT_VER=${VERSION_ID}")
target_compile_options(position PRIVATE -Wall -pedantic -Wextra)
set_target_properties (position PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS FALSE
)
add_subdirectory(plotter)
