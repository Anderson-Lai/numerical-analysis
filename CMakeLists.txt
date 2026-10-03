cmake_minimum_required(VERSION 3.20)

project(numerical_calculus CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer/lexer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer/types.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/calculus/differentiator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/calculus/integrator.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/binary_operators.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/lexer/
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/parser/
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/calculus/
)

# define DEBUG_BUILD macro for Debug build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD)
endif()