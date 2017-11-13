cmake_minimum_required(VERSION 3.8)
project(Delegates)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BaseDelegate.h Delegate.h)
add_executable(Delegates ${SOURCE_FILES})