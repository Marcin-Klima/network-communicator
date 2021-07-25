cmake_minimum_required(VERSION 3.19)
project(network_communicator)

set(CMAKE_CXX_STANDARD 20)

add_executable(network_communicator  main.cpp)

target_include_directories(network_communicator PRIVATE external)