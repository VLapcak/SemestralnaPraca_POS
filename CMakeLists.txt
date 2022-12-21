cmake_minimum_required(VERSION 3.23)
project(Semestralka_lapcak_ihring)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR SDL/include)
set(SDL2_LIB_DIR SDL/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(Semestralka_lapcak_ihring main.cpp)

target_link_libraries(${PROJECT_NAME} SDL/lib/x86/SDL2main SDL/lib/x86/SDL2)