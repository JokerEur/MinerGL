cmake_minimum_required(VERSION 3.8)

project(SnakeGL)

set(CMAKE_CXX_STANDARD 20)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
include_directories("${PROJECT_SOURCE_DIR}/include")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB CPP_SOURCES "scr/*.cpp")

add_executable(${PROJECT_NAME} main.cpp)



target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
