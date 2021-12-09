cmake_minimum_required(VERSION 3.19)

project(network_communicator)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
	message(STATUS "DUPA")
	add_compile_options(/W4 /WX)
	add_compile_definitions(_WIN32_WINNT=0x0601)
	if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
		add_compile_options(/Od /Zi)
	endif()
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
	if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
		add_compile_options(-O0 -g)
	endif()
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	include(conan-debug/conanbuildinfo.cmake)
elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
	include(conan-release/conanbuildinfo.cmake)
endif()

conan_basic_setup()

find_package(Qt5 COMPONENTS Widgets Qml Quick QuickCompiler REQUIRED)
add_compile_options(${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS})

add_subdirectory(server)
add_subdirectory(client)