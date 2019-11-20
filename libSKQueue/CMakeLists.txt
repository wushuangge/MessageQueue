cmake_minimum_required(VERSION 3.10)
project(skqueue)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SRC_LIST "*.cpp")
file(GLOB HEADERS "*.h")

add_library(skqueue STATIC ${SRC_LIST} ${HEADERS})