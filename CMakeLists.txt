
cmake_minimum_required(VERSION 3.10.1)
project(Pacman)

file(GLOB SOURCE "${PROJECT_SOURCE_DIR}/src/*")
add_executable(Pacman ${SOURCE})
include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(lib STATIC IMPORTED)
set_target_properties(lib PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/liblib.a")
target_link_libraries(Pacman lib)
target_link_libraries(Pacman m SDL2 SDL2_gfx)
add_definitions(-D_REENTRANT)

