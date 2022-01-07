set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
qtquick_compiler_add_resources(QT_RESOURCES ui/qml.qrc)

add_executable(klima-client ${QT_RESOURCES})

target_sources(klima-client PRIVATE
		src/main.cpp
		src/Frontend.cpp

		src/Frontend.h
)

target_link_libraries(klima-client
		${CONAN_LIBS}
		Qt5::Quick
		Qt5::Widgets
		Qt5::Qml
)

target_include_directories(klima-client PRIVATE
		${PROJECT_SOURCE_DIR}/common
		${CONAN_INCLUDE_DIRS}
		${Qt5Widgets_INCLUDE_DIRS}
		${QtQml_INCLUDE_DIRS}
)

target_compile_definitions(klima-client PRIVATE
		${Qt5Widgets_DEFINITIONS}
		${QtQml_DEFINITIONS}
		${${Qt5Quick_DEFINITIONS}}
)

include(example.cmake)