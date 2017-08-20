cmake_minimum_required(VERSION 3.7)
project(3DTetris)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Cube.cpp Cube.h Functions.cpp Functions.h UI.cpp UI.h Glut.h Window.cpp Window.h Graph.cpp Graph.h Controls.cpp Controls.h Generator.cpp Generator.h KeyboardCommands.cpp KeyboardCommands.h)
add_executable(3DTetris ${SOURCE_FILES})


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(3DTetris ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

#INSTALL TO MAKE YOUR LIFE EASIER

#sudo apt-get install freeglut3-dev
#sudo apt-get install libxmu-dev libxi-dev