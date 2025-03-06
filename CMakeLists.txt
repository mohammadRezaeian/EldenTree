cmake_minimum_required(VERSION 3.30)
project(EldenTree VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")

include_directories(${PROJECT_SOURCE_DIR}/Include)

file(GLOB_RECURSE HEADER_FILES "Include/*.h")


option(BUILD_MAIN "Do you want build main software?!" OFF)
option(BUILD_TEST "Do you want build Test software?!" ON)



if (BUILD_MAIN)
    add_executable(EldenTree ${PROJECT_SOURCE_DIR}/Src/main.cpp ${HEADER_FILES})
endif ()

if (BUILD_TEST)
    add_subdirectory(Test)
endif ()
