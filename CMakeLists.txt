cmake_minimum_required(VERSION 3.20)

project(chess C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED COMPONENTS SDL3)
find_package(SDL3_image CONFIG REQUIRED)

add_executable(chess
    main.c
    gameFunctions.c
    displayFunctions.c
)

target_include_directories(chess PRIVATE headers)

target_link_libraries(chess PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

add_custom_command(TARGET chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:chess>/assets
)