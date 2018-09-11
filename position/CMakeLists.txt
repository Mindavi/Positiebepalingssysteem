cmake_minimum_required(VERSION 3.1)
project(position2)
add_executable(position2 position.cpp)
target_link_libraries(position2 opencv_core opencv_highgui opencv_videoio opencv_imgproc opencv_video)
target_compile_options(position2 PRIVATE -Wall -pedantic -Wextra)
set_target_properties (position2 PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS FALSE
)
