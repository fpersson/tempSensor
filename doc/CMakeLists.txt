find_package(Doxygen REQUIRED)

get_target_property(LIBMQTT_PUBLIC_HEADER_DIR libmqtt INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE LIBMQTT_PUBLIC_HEADER_DIR ${LIBMQTT_PUBLIC_HEADER_DIR})

get_target_property(LIBSENSOR_PUBLIC_HEADER_DIR libsensor INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE LIBSENSOR_PUBLIC_HEADER_DIR ${LIBSENSOR_PUBLIC_HEADER_DIR})

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/libmqtt/src)
set(DOXYGEN_SENSOR_DIR ${PROJECT_SOURCE_DIR}/libsensor/src)
set(DOXYGEN_UTILS_DIR ${PROJECT_SOURCE_DIR}/libutils/src)
set(DOXYGEN_MAIN_PAGE ${PROJECT_SOURCE_DIR}/README.md)

set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
        DEPENDS ${LIBMQTT_PUBLIC_HEADER_DIR}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
        COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

find_package(Sphinx REQUIRED)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/docs/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
        COMMAND
        ${SPHINX_EXECUTABLE} -b html
        # Tell Breathe where to find the Doxygen output
        -Dbreathe_projects.Tempsensor=${DOXYGEN_OUTPUT_DIR}/xml
        ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS
        # Other docs files you want to track should go here (or in some variable)
        ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
        ${CMAKE_CURRENT_SOURCE_DIR}/libsensor.rst
        ${CMAKE_CURRENT_SOURCE_DIR}/libutils.rst
        ${DOXYGEN_INDEX_FILE}
        MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
        COMMENT "Generating documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})
