cmake_minimum_required(VERSION 3.7)
project(tempsensor)

#Option activate with -Dunittest=ON
option(unittest "Build unittest." OFF)

#uncomment to as devel
#add_definitions(-DDEVEL)

#uncomment to in debug
#add_definitions(-DDEBUGMODE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package (SQLite3 REQUIRED)
set(SQLITE3_LIBRARY "-lsqlite3")
include_directories(${SQLITE3_INCLUDE_DIRS})

find_package(Mosquitto)
include_directories(${MOSQUITTO_INCLUDE_DIRS})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(libutils)
add_subdirectory(libmqtt)
add_subdirectory(libsensor)

add_executable(tempsensor main.cpp ${SOURCE_FILES})
target_link_libraries(tempsensor libutils libmqtt libsensor ${SQLITE3_LIBRARY} ${MOSQUITTO_LIBRARIES})

if(unittest)
    add_subdirectory(googletest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    #Unittests
    add_executable(runUnitTests libutils/tests/test_utils.cpp)
    target_link_libraries(runUnitTests gtest gtest_main)
    target_link_libraries(runUnitTests libutils)
endif()
