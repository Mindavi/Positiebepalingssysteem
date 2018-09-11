cmake_minimum_required(VERSION 3.1)
project(position_from_camera)

add_executable(position_from_camera position_from_camera.cpp)
include_directories("${PROJECT_BINARY_DIR}")
target_link_libraries(position_from_camera opencv_core opencv_highgui opencv_videoio)
execute_process(COMMAND git describe --long --tags --dirty OUTPUT_VARIABLE VERSION_ID)
target_compile_definitions(position_from_camera PRIVATE "EXT_VER=${VERSION_ID}")
target_compile_options(position_from_camera PRIVATE -Wall -pedantic -Wextra)

set_target_properties (position_from_camera PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS FALSE
)

add_subdirectory(position)
add_subdirectory(plotter)