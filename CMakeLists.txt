cmake_minimum_required(VERSION 3.17)
project(calculator)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES main.cpp node.cpp parser.cpp visitor.cpp)
set(HEADERS node.h parser.h visitor.h)

add_executable(calculator ${SOURCES} ${HEADERS})