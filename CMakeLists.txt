cmake_minimum_required(VERSION 3.18)
project(Semestralka_lapcak_ihring)

set(CMAKE_CXX_STANDARD 14)




#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR SFML/lib/cmake/SFML)

#include_directories(SFML/include)
#target_link_libraries(Semestralka_lapcak_ihring sfml-system sfml-window sfml-graphics sfml-audio)

set(SDL2_INCLUDE_DIR SDL2/include)
set(SDL2_LIB_DIR SDL2/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(Semestralka_lapcak_ihring main.cpp)

target_link_libraries(Semestralka_lapcak_ihring SDL2main SDL2)