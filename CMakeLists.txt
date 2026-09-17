cmake_minimum_required(VERSION 3.20)

project(numerical_calculus CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/differentiator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/integrator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/types.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

# define DEBUG_BUILD macro for Debug build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD)
endif()