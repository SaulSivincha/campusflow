cmake_minimum_required(VERSION 3.16)
project(CampusFlow VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(campusflow_core src/Campus.cpp)
target_include_directories(campusflow_core PUBLIC include)

add_executable(campusflow src/main.cpp)
target_link_libraries(campusflow PRIVATE campusflow_core)
