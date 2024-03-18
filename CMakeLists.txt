# ~~~~~~Basic CMakeList Settings~~~~~~
cmake_minimum_required(VERSION 3.22)
project(Lab1 C)

set(CMAKE_C_STANDARD 11)

# ~~~~~~Variables~~~~~~
set(RequiredMinimumVersion_Flex 2.5.35)
set(RequiredMinimumVersion_Bison 2.5.0)
set(MainTarget Lab1)
set(MainSourceFile main.c)
# ~~~~~~End of Variables~~~~~~

# Find Flex and Bison
find_package(FLEX REQUIRED)

if(NOT FLEX_FOUND)
    message(FATAL_ERROR "Flex is not found on your system.")
elseif(${FLEX_VERSION} VERSION_LESS ${RequiredMinimumVersion_Flex})
    message(FATAL_ERROR "Flex version is less than the required minimum version. Required: ${FLEX_VERSION}")
endif()

find_package(BISON REQUIRED)


if(NOT BISON_FOUND)
    message(FATAL_ERROR "Bison is not found on your system.")
elseif(${BISON_VERSION} VERSION_LESS ${RequiredMinimumVersion_Bison})
    message(FATAL_ERROR "Bison version is less than the required minimum version. Required: ${BISON_VERSION}")
endif()

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Collect source files
aux_source_directory(src SRC)
include_directories(include)

# Generate lexer and parser
flex_target(Lexer src/C_Scanner.l ${CMAKE_CURRENT_BINARY_DIR}/C_Scanner.c)
bison_target(Parser src/C_Parser.y ${CMAKE_CURRENT_BINARY_DIR}/C_Parser.c DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/C_Parser.tab.h COMPILE_FLAGS "-d")
add_flex_bison_dependency(Lexer Parser)

# Add lexer and parser to the project
add_library(Lexer STATIC ${FLEX_Lexer_OUTPUTS})
add_library(Parser STATIC ${BISON_Parser_OUTPUTS})

# Add Libs
add_library(SimpleArray STATIC src/SimpleArray.c )

# Compile the project
add_executable(${MainTarget} ${MainSourceFile}
        src/SymbolName.c)
target_link_libraries(Lexer ${FLEX_LIBRARIES})
target_link_libraries(Parser ${BISON_LIBRARIES})
target_link_libraries(${MainTarget} Lexer Parser SimpleArray)