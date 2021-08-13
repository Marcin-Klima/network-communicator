add_executable(klima-server)

target_sources(klima-server PRIVATE
		src/main.cpp
		src/Server.cpp
		src/TerminalInterface.cpp

		src/Server.h
		src/TerminalInterface.h
)

target_compile_definitions(klima-server PRIVATE _WIN32_WINNT=0x0601)

target_link_libraries(klima-server ${CONAN_LIBS})
target_include_directories(klima-server PRIVATE
		${PROJECT_SOURCE_DIR}/common
		${CONAN_INCLUDE_DIRS}
)