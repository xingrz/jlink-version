cmake_minimum_required(VERSION 3.10)

project(jlink-version)

add_executable(
    ${PROJECT_NAME}
    src/main.c
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
