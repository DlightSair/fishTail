cmake_minimum_required(VERSION 3.20)

project(chess C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED COMPONENTS SDL3)

add_executable(chess 
    main.c
    gameFunctions.c
    displayFunctions.c
)

target_include_directories(chess PRIVATE headers)

target_link_libraries(chess PRIVATE SDL3::SDL3)