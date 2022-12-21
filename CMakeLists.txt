cmake_minimum_required(VERSION 3.18)
project(Semestralka_lapcak_ihring)

set(CMAKE_CXX_STANDARD 14)

add_executable(Semestralka_lapcak_ihring main.cpp HraciaPlocha.cpp)


#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR SFML/lib/cmake/SFML)

#add_executable(Semestralka_lapcak_ihring main.cpp)

#include_directories(SFML/include)
#target_link_libraries(Semestralka_lapcak_ihring sfml-system sfml-window sfml-graphics sfml-audio)

#set(SDL2_INCLUDE_DIR SDL2/include)
#set(SDL2_LIB_DIR SDL2/lib/x86)

#include_directories(${SDL2_INCLUDE_DIR})
#link_directories(${SDL2_LIB_DIR})


#target_link_libraries(Semestralka_lapcak_ihring SDL2main SDL2)