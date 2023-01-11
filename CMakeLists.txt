cmake_minimum_required(VERSION 3.18)
project(Semestralka_lapcak_ihring)

set(CMAKE_CXX_STANDARD 14)

add_executable(Semestralka_lapcak_ihring main.cpp HraciaPlocha.cpp Hrac.cpp Figurka.cpp Kocka.cpp Manazer.cpp Tcp_server.cpp)
add_executable(klient Tcp_client.cpp)
target_link_libraries(Semestralka_lapcak_ihring pthread)
target_link_libraries(klient pthread)
