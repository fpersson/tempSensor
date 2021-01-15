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
add_subdirectory(doc)

add_executable(tempsensor main.cpp ${SOURCE_FILES})
target_link_libraries(tempsensor libutils libmqtt libsensor ${SQLITE3_LIBRARY} ${MOSQUITTO_LIBRARIES})

if(unittest)
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    message(${CMAKE_CURRENT_BINARY_DIR})
    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
            ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
            EXCLUDE_FROM_ALL)

    add_executable(runUnitTests libutils/tests/test_utils.cpp)
    target_link_libraries(runUnitTests gtest gtest_main)
    target_link_libraries(runUnitTests libutils)
endif()
