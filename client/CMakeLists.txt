add_executable(klima-client)

target_sources(klima-client PRIVATE
		src/main.cpp
)

target_link_libraries(klima-client ${CONAN_LIBS})
target_include_directories(klima-client PRIVATE
		${PROJECT_SOURCE_DIR}/common
		${CONAN_INCLUDE_DIRS}
)