cmake_minimum_required(VERSION 3.21)
project(CWK2 C)

set(CMAKE_C_STANDARD 99)

include_directories(SDL)

add_executable(CWK2 main.c evolution.c evolution.h generate.c generate.h
        user.c user.h interface.c interface.h)

target_link_libraries(CWK2 mingw32 SDL2main SDL2)




