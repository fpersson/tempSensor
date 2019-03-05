cmake_minimum_required(VERSION 3.10)
project(tempsensor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)

set(SOURCE_FILES

)

add_executable(tempsensor main.cpp ${SOURCE_FILES})
target_link_libraries(tempsensor Qt5::Core)
