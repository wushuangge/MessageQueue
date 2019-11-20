cmake_minimum_required(VERSION 3.10)
project(src)

set(CMAKE_CXX_STANDARD 11)

# Use ISO C++11 standard language.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -fPIC")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -fPIC")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)

include_directories(SKQueue)
include_directories(test)

add_executable(src
        SKQueue/Dispatcher.cpp
        SKQueue/Dispatcher.h
        SKQueue/HandlerFactory.cpp
        SKQueue/HandlerFactory.h
        SKQueue/IHandler.h
        SKQueue/Log.h
        SKQueue/MessageQueue.cpp
        SKQueue/MessageQueue.h
        test/main.cpp)
