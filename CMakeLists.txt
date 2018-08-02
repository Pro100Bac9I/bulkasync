cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 0)
endif()

project(async VERSION 0.0.${VERSION_BUILD})

add_subdirectory(bulk)

add_library(async 

	SHARED
	async.cpp
	HandlersCollection.cpp
)

target_link_libraries(async bulk_lib)

add_executable(async_test main.cpp)

set_target_properties(
    async
    async_test

    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

target_link_libraries(
    async_test
    async
    -pthread
)

install(TARGETS 
	async_test async
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT erkinvs@gmail.com)

include(CPack)