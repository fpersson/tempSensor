add_library(libutils
        src/IOhelper.cpp
        src/IOhelper.h
        src/IniParser.cpp
        src/IniParser.h
        src/History.h
        src/History.cpp
        src/HistoryData.h
        src/Keys.h
        src/TimerTask.h
        src/TimerTask.cpp
        src/FObserver.h
)

target_include_directories(libutils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
