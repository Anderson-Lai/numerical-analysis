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

    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/trigonometry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/logarithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/sqrt_cbrt.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/statement_number.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/statement_variable.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/tree.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

# define DEBUG_BUILD macro for Debug build type and also add address sanitizer
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD)

    target_compile_options(${PROJECT_NAME} PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        -fsanitize=address
    )
endif()