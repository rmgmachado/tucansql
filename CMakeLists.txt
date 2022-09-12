cmake_minimum_required(VERSION 3.10)

# set the project name
project(tucansql)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 17)

# include folders
include_directories(src tests)

find_package(BISON)
BISON_TARGET(syntax src/sqlsyntax.y "${CMAKE_CURRENT_BINARY_DIR}/sqlsyntax.cpp" COMPILE_FLAGS "-d --no-lines -p sql_" )

# add the executable
add_executable(tucansql tests/test_datetime.cpp tests/test_decimal.cpp tests/test_memdb.cpp 
                        tests/test_scanner.cpp tests/test_sqlparser.cpp 
                        tests/test_tucansql.cpp tests/xpunit.cpp 
                        ${BISON_syntax_OUTPUT_SOURCE})