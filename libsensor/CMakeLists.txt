add_library(libsensor
        src/SensorCore.cpp
        src/SensorCore.h
        src/DBManager.cpp
        src/DBManager.h
        src/MqttClient.cpp
        src/MqttClient.h
)

target_link_libraries(libsensor
        ${MQTT_LIB}
        libutils
        libmqtt
)

target_include_directories(libsensor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")