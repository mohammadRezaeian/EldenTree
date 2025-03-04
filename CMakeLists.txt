cmake_minimum_required(VERSION 3.30)
project(EldenTree VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/Include)

add_executable(EldenTree main.cpp)
