cmake_minimum_required(VERSION 3.19)

project(network_communicator)

set(CMAKE_CXX_STANDARD 20)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	include(conan-debug/conanbuildinfo.cmake)
elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
	include(conan-release/conanbuildinfo.cmake)
endif()

conan_basic_setup()

find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)

add_subdirectory(server)
add_subdirectory(client)