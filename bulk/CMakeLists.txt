cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 0)
endif()

message(STATUS "Build number: " ${VERSION_BUILD})

project(bulk_lib VERSION 0.0.${VERSION_BUILD})

add_library(
    bulk_lib 

	CommandBlock.cpp
	LineProcessor.cpp
	Observer.cpp
	TimedBlock.cpp
)

set_target_properties(
    bulk_lib

    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)