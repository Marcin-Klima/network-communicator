add_executable(client-example)
target_sources(client-example PRIVATE
        src/example.cpp
)
target_include_directories(client-example PRIVATE
        ${PROJECT_SOURCE_DIR}/common
        ${CONAN_INCLUDE_DIRS}
)
target_link_libraries(client-example
        ${CONAN_LIBS}
)