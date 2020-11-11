add_library(libmqtt
    src/Mqtt.h
    src/Mqtt.cpp
)

target_link_libraries(libmqtt
        ${MQTT_LIB}
        libutils
)

target_include_directories(libmqtt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")