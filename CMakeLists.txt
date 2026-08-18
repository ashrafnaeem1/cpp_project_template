cmake_minimum_required(VERSION 4.3)

project(ProjectName)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
add_executable(main)
target_sources(main
    PRIVATE
    ./src/main.cxx
)
add_library(Helpers)
target_sources(Helpers
    PRIVATE
    ./src/Helpers.cxx

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
    ./include
    FILES
    ./include/Helpers.h
)
target_link_libraries(main
    PRIVATE
    Helpers
)
