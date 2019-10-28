cmake_minimum_required(VERSION 3.15)
project(lr5)

set(CMAKE_CXX_STANDARD 14)

add_executable(lr5 main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(lr5 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

configure_file(object_data object_data COPYONLY)
configure_file(arc_points arc_points COPYONLY)