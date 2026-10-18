cmake_minimum_required(VERSION 3.25)

# MSVC's default debug format (/ZI, "Edit and Continue") is incompatible with ASan.
# Must be set before project().
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>")

project(numerical_analysis LANGUAGES CXX)

# ---------------- Options ----------------
option(ENABLE_ASAN                             "Enable AddressSanitizer in Debug builds"        ON)
option(ENABLE_UBSAN                            "Enable UBSan in Debug builds (GCC/Clang)"       ON)
option(DEBUG_EXPRESSIONS                       "Define DEBUG_EXPRESSIONS"                       OFF)
option(DEBUG_EXPRESSIONS_WITH_NEGATIVE_NUMBERS "Define DEBUG_EXPRESSIONS_WITH_NEGATIVE_NUMBERS" OFF)
option(DEBUG_SINGLE_THREAD                     "Define DEBUG_SINGLE_THREAD"                     OFF)

# ---------------- Language standard ----------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # -std=c++20 instead of -std=gnu++20

# MSVC's default Debug flags include /RTC1 (runtime checks), which conflicts with ASan.
if(MSVC AND ENABLE_ASAN)
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
endif()

# ---------------- Target ----------------
add_executable(${PROJECT_NAME}
    src/main.cpp

    src/lexer/lexer.cpp
    src/lexer/types.cpp

    src/analysis/derivative.cpp
    src/analysis/integral.cpp
    src/analysis/limit.cpp
    src/analysis/root.cpp
    src/analysis/series.cpp

    src/parser/binary_operators.cpp
    src/parser/function_argument.cpp
    src/parser/trigonometry.cpp
    src/parser/logarithm.cpp
    src/parser/sqrt_cbrt.cpp
    src/parser/statement_number.cpp
    src/parser/statement_variable.cpp
    src/parser/parser.cpp
    src/parser/tree.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# ---------------- Threads (replaces -pthread) ----------------
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# ---------------- Definitions (all compilers) ----------------
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG_BUILD>
    $<$<BOOL:${DEBUG_EXPRESSIONS}>:DEBUG_EXPRESSIONS>
    $<$<BOOL:${DEBUG_EXPRESSIONS_WITH_NEGATIVE_NUMBERS}>:DEBUG_EXPRESSIONS_WITH_NEGATIVE_NUMBERS>
    $<$<BOOL:${DEBUG_SINGLE_THREAD}>:DEBUG_SINGLE_THREAD>
)

# ---------------- Link-time optimization (Release) ----------------
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_ERROR)
if(IPO_SUPPORTED)
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
else()
    message(STATUS "LTO not supported: ${IPO_ERROR}")
endif()

# ---------------- Compiler-specific flags ----------------
if(MSVC)
    # ---------- MSVC / clang-cl ----------
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4              # ~ -Wall -Wextra
        /permissive-     # strict standards conformance (~ -Wpedantic)
        /utf-8           # UTF-8 source + execution charset
        /Zc:__cplusplus  # report the real __cplusplus value
        /Zc:preprocessor # standards-conforming preprocessor
        /MP              # parallel compilation

        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Release>:/Gy>   # function-level linking (needed for /OPT:REF)
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        NOMINMAX                   # stop windows.h defining min/max macros
        WIN32_LEAN_AND_MEAN
        _CRT_SECURE_NO_WARNINGS
    )

    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/OPT:REF>   # remove unused code
        $<$<CONFIG:Release>:/OPT:ICF>   # fold identical functions
    )

    if(ENABLE_ASAN)
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:/fsanitize=address>
        )
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:/INCREMENTAL:NO>  # ASan is incompatible with incremental linking
        )
    endif()
else()
    # ---------- GCC / Clang ----------
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion

        $<$<CONFIG:Debug>:-Og>
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Debug>:-ggdb>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>

        $<$<CONFIG:Release>:-O3>
    )

    if(NOT APPLE)
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:-s>   # strip symbols
        )
    endif()

    if(ENABLE_ASAN)
        target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)
        target_link_options(${PROJECT_NAME}    PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)
    endif()

    if(ENABLE_UBSAN)
        target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-fsanitize=undefined>)
        target_link_options(${PROJECT_NAME}    PRIVATE $<$<CONFIG:Debug>:-fsanitize=undefined>)
    endif()
endif()