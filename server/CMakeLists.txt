set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
qtquick_compiler_add_resources(QT_RESOURCES src/qml.qrc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

add_executable(klima-server ${QT_RESOURCES})

target_sources(klima-server PRIVATE
		src/main.cpp
		src/Server.cpp
		src/FrontendServerMediator.cpp

		src/Server.h
		src/FrontendServerMediator.h
)

target_compile_definitions(klima-server PRIVATE _WIN32_WINNT=0x0601)

message(STATUS ${CONAN_LIBS})

target_link_libraries(klima-server
		${CONAN_LIBS}
#		Qt5::Core
		Qt5::Quick
		Qt5::Widgets
		Qt5::Qml
)

target_include_directories(klima-server PRIVATE
		${PROJECT_SOURCE_DIR}/common
		${CONAN_INCLUDE_DIRS}
		${Qt5Widgets_INCLUDE_DIRS}
		${QtQml_INCLUDE_DIRS}
)

target_compile_definitions(klima-server PRIVATE
		${Qt5Widgets_DEFINITIONS}
		${QtQml_DEFINITIONS}
		${${Qt5Quick_DEFINITIONS}}
)
