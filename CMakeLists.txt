cmake_minimum_required(VERSION 3.7)
project(tempsensor)

#Option activate with -Dunittest=ON
option(unittest "Build unittest." OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -std=c++14")

find_package(CURL REQUIRED)
set(CURL_LIBRARY "-lcurl")
include_directories(${CURL_INCLUDE_DIR})

set(SOURCE_FILES
        TimerTask.cpp
        TimerTask.h
        SensorCore.cpp
        SensorCore.h
        FObserver.h
        CurlFirebase.cpp
        CurlFirebase.h
        )

set(lib_utils_SRC
        IOhelper.cpp
        IOhelper.h
        IniParser.cpp
        IniParser.h
        )

add_library(lib_utils ${lib_utils_SRC})

add_executable(tempsensor main.cpp ${SOURCE_FILES})
target_link_libraries(tempsensor lib_utils ${CURL_LIBRARIES})

if(unittest)
    add_subdirectory(googletest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    #Unittests
    add_executable(runUnitTests unit_tests/test_main.cpp)
    target_link_libraries(runUnitTests gtest gtest_main)
    target_link_libraries(runUnitTests lib_utils)
endif()
