cmake_minimum_required(VERSION 3.10)
project(tempsensor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -std=c++14")

set(SOURCE_FILES
        TimerTask.cpp
        TimerTask.h
)

add_executable(tempsensor main.cpp ${SOURCE_FILES})
target_link_libraries(tempsensor)
