cmake_minimum_required(VERSION 3.10)

# set the project name
project(tucansql)

include_directories(src tests)

# add the executable
add_executable(tucansql src/sqlsyntax.cpp tests/test_datetime.cpp 
                        tests/test_decimal.cpp tests/test_memdb.cpp 
                        tests/test_scanner.cpp tests/test_sqlparser.cpp
                        tests/test_tucansql.cpp tests/xpunit.cpp)