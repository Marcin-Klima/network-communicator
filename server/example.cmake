add_executable(server-example)
target_sources(server-example PRIVATE
        src/example.cpp
)
target_include_directories(server-example PRIVATE
        ${PROJECT_SOURCE_DIR}/common
        ${CONAN_INCLUDE_DIRS}
)
target_link_libraries(server-example
        ${CONAN_LIBS}
)