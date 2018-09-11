cmake_minimum_required(VERSION 3.1)
project(view_library)
add_library(view_library ImageReader.cpp Log.cpp print_image.cpp)
target_link_libraries(view_library opencv_core opencv_imgcodecs opencv_imgproc)
target_compile_options(view_library PRIVATE -Wall -pedantic -Wextra)
set_target_properties (view_library PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS FALSE
)
