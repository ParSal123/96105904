
cmake_minimum_required(VERSION 3.10.1)
project(Pacman)

file(GLOB SOURCE "src/*")
add_executable(Pacman ${SOURCE})
include_directories("include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
target_link_libraries(Pacman m SDL2 SDL2_gfx)
add_definitions(-D_REENTRANT)

