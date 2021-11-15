cmake_minimum_required(VERSION 3.10)

project(jlink-version)

add_executable(
    ${PROJECT_NAME}
    src/main.c
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

if(WIN32)
    add_subdirectory(dlfcn-win32/src)
    target_link_libraries(${PROJECT_NAME} dl)
    target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/dlfcn-win32/src)
else()
    target_link_libraries(${PROJECT_NAME} -ldl)
endif()
