cmake_minimum_required(VERSION 3.1)
project(view)
add_executable(view view.cpp)
include_directories(lib)
target_link_libraries(view PRIVATE opencv_core opencv_highgui opencv_imgproc)
target_compile_options(view PRIVATE -Wall -pedantic -Wextra)
set_target_properties (view PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS FALSE
)
add_subdirectory(lib)
target_link_libraries(view PRIVATE view_library)