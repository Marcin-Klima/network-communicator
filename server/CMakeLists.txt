set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
qtquick_compiler_add_resources(QT_RESOURCES ui/qml.qrc)

add_executable(klima-server ${QT_RESOURCES})

target_sources(klima-server PRIVATE
		src/main.cpp
		src/Server.cpp
		src/Session.cpp

		src/Server.h
		src/Session.h
)

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

include(example.cmake)