cmake_minimum_required(VERSION 3.7)
project(3DTetris)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp cube.cpp cube.h)
add_executable(3DTetris ${SOURCE_FILES})


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(3DTetris ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

#INSTALL TO MAKE YOUR LIFE EASIER

#sudo apt-get install freeglut3-dev
#sudo apt-get install libxmu-dev libxi-dev