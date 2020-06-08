cmake_minimum_required(VERSION 3.16)
project(grbl)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -msse3")

if (APPLE)
    add_compile_definitions(Q_OS_MAC)
endif ()

find_package(Qt5 COMPONENTS Core Widgets OpenGL SerialPort REQUIRED)
find_package(Qt5 COMPONENTS Test REQUIRED)

include_directories(cmake-build-debug/Viewer_autogen/include)

include_directories(src/widgets)

set(
        SOURCES_WIDGETS
        src/widgets/console/ConsoleWidget.cpp
        src/widgets/console/ConsoleWidget.h
        src/widgets/serialPort/SerialPortWidget.cpp
        src/widgets/serialPort/SerialPortWidget.h
        src/widgets/status/StatusWidget.cpp
        src/widgets/status/StatusWidget.h
        src/widgets/vec3/Vec3Widget.cpp
        src/widgets/vec3/Vec3Widget.h
        src/widgets/welcome/WelcomeWidget.cpp src/widgets/welcome/WelcomeWidget.h)

set(
        SOURCES_PARSER_STATUS_REPORT
        src/grbl/GRBL.cpp
        src/grbl/GRBL.h
        src/grbl/parsers/status_report/accessory_state/AccessoryStateParser.cpp
        src/grbl/parsers/status_report/accessory_state/AccessoryStateParser.h
        src/grbl/parsers/status_report/buffer_state/BufferStateParser.cpp
        src/grbl/parsers/status_report/buffer_state/BufferStateParser.h
        src/grbl/parsers/status_report/feed_rate/FeedRateParser.cpp
        src/grbl/parsers/status_report/feed_rate/FeedRateParser.h
        src/grbl/parsers/status_report/feed_rate_spindle_speed/FeedRateAndSpindleSpeedParser.cpp
        src/grbl/parsers/status_report/feed_rate_spindle_speed/FeedRateAndSpindleSpeedParser.h
        src/grbl/parsers/status_report/input_pin_state/InputPinStateParser.cpp
        src/grbl/parsers/status_report/input_pin_state/InputPinStateParser.h
        src/grbl/parsers/status_report/line_number/LineNumberParser.cpp
        src/grbl/parsers/status_report/line_number/LineNumberParser.h
        src/grbl/parsers/status_report/machine_state/MachineStateParser.cpp
        src/grbl/parsers/status_report/machine_state/MachineStateParser.h
        src/grbl/parsers/status_report/overridden_values/OverriddenValuesParser.cpp
        src/grbl/parsers/status_report/overridden_values/OverriddenValuesParser.h
        src/grbl/parsers/status_report/position_parser/PositionParser.cpp
        src/grbl/parsers/status_report/position_parser/PositionParser.h
        src/grbl/vec3/vec3.cpp
        src/grbl/vec3/vec3.h
)

set(
        SOURCES_GRBL
        ${SOURCES_PARSER_STATUS_REPORT}
        src/grbl/parsers/welcome_message/WelcomeMessageParser.cpp
        src/grbl/parsers/welcome_message/WelcomeMessageParser.h
)

set(
        SOURCES
        src/MainWindow.cpp
        src/SerialPort.cpp
        src/SerialPort.h
        ${SOURCES_GRBL}
        ${SOURCES_WIDGETS}
)

add_executable(grbl
        src/main.cpp
        ${SOURCES}
        )

target_link_libraries(grbl
        Qt5::Widgets
        Qt5::SerialPort)

add_executable(
        grbl-test
        tests/main.cpp
        tests/TestSuite.cpp
        tests/TestSuite.h
        ${SOURCES_GRBL}
        src/grbl/GRBL.test.cpp
        src/grbl/parsers/status_report/accessory_state/AccessoryStateParser.test.cpp
        src/grbl/parsers/status_report/buffer_state/BufferStateParser.test.cpp
        src/grbl/parsers/status_report/feed_rate/FeedRateParser.test.cpp
        src/grbl/parsers/status_report/feed_rate_spindle_speed/FeedRateAndSpindleSpeedParser.test.cpp
        src/grbl/parsers/status_report/input_pin_state/InputPinStateParser.test.cpp
        src/grbl/parsers/status_report/line_number/LineNumberParser.test.cpp
        src/grbl/parsers/status_report/machine_state/MachineStateParser.test.cpp
        src/grbl/parsers/status_report/overridden_values/OverridenValuesParser.test.cpp
        src/grbl/parsers/status_report/position_parser/PositionParser.test.cpp
        src/grbl/parsers/welcome_message/WelcomeMessageParser.test.cpp)

target_link_libraries(
        grbl-test
        Qt5::Widgets
        Qt5::SerialPort
        Qt5::Test
)
