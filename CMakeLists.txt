cmake_minimum_required(VERSION 3.10)
project(tempsensor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -std=c++14")

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

set(SOURCE_FILES
        TimerTask.cpp
        TimerTask.h
        SensorCore.cpp
        SensorCore.h
        IOhelper.cpp
        IOhelper.h
        FObserver.h
        CurlFirebase.cpp
        CurlFirebase.h)

add_executable(tempsensor main.cpp ${SOURCE_FILES})
target_link_libraries(tempsensor ${CURL_LIBRARIES})
