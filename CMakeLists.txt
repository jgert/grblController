cmake_minimum_required(VERSION 3.15)
project(grbl)

set(CMAKE_CXX_STANDARD 20)

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
        SOURCES_GCODE
        src/gCode/Parser.cpp
        src/gCode/Parser.h
        src/gCode/split.cpp
        src/gCode/split.h
)

set(
        SOURCES_GCODE_TEST
        src/gCode/Parser.test.cpp
        src/gCode/split.test.cpp
)

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
        src/widgets/welcome/WelcomeWidget.cpp
        src/widgets/welcome/WelcomeWidget.h
        src/widgets/settings/SettingsWidget.cpp
        src/widgets/settings/SettingsWidget.h
        src/utils/AlarmCodes.cpp
        src/utils/AlarmCodes.h
        src/widgets/alarm/AlarmWidget.cpp
        src/widgets/alarm/AlarmWidget.h
        src/utils/AlarmCodes.h
        src/widgets/alarm/AlarmWidget.cpp
        src/widgets/alarm/AlarmWidget.h
        src/widgets/codeEditor/CodeEditorWidget.cpp
        src/widgets/codeEditor/CodeEditorWidget.h
        src/widgets/codeEditor/LineNumberWidget.h
        src/widgets/codeEditor/GCodeEditorWidget.cpp
        src/widgets/codeEditor/GCodeEditorWidget.h
        src/widgets/render/Renderer3DWidget.cpp
        src/widgets/render/Renderer3DWidget.h
        src/widgets/codeEditor/GCodeSyntaxHighlighter.cpp
        src/widgets/codeEditor/GCodeSyntaxHighlighter.h
)

set(
        SOURCES_PARSER_STATUS_REPORT
        src/grbl/GRBL.cpp
        src/grbl/GRBL.h
        src/grbl/Message.cpp
        src/grbl/Message.h
        src/grbl/parsers/alarm/AlarmParser.cpp
        src/grbl/parsers/alarm/AlarmParser.h
        src/grbl/parsers/help/HelpParser.cpp
        src/grbl/parsers/help/HelpParser.h
        src/grbl/parsers/response_message/ResponseMessageParser.cpp
        src/grbl/parsers/response_message/ResponseMessageParser.h
        src/grbl/parsers/setting/SettingParser.cpp
        src/grbl/parsers/setting/SettingParser.h
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
        src/grbl/parsers/welcome_message/WelcomeMessageParser.cpp
        src/grbl/parsers/welcome_message/WelcomeMessageParser.h
        src/grbl/vec3/vec3.cpp
        src/grbl/vec3/vec3.h
        src/utils/SettingCodes.cpp
        src/utils/SettingCodes.h
)

set(
        SOURCES_GRBL
        ${SOURCES_PARSER_STATUS_REPORT}
)

set(
        SOURCES_MACHINE
        src/machine/Engraver3axis.cpp
        src/machine/Engraver3axis.h
        src/machine/Machine.h
        src/machine/Engraver3axis.Machine.cpp
        src/machine/Engraver3axis.G00.cpp
        src/machine/Engraver3axis.G01.cpp
        src/machine/Engraver3axis.G20.cpp
        src/machine/Engraver3axis.G21.cpp
        src/machine/Engraver3axis.G90.cpp
        src/machine/Engraver3axis.G91.cpp
)

set(
        SOURCES_MACHINE_TESTS
        src/machine/Engraver3axis.G00.test.cpp
        src/machine/Engraver3axis.G01.test.cpp src/machine/Engraver3axis.G20.test.cpp src/machine/Engraver3axis.G21.test.cpp src/machine/Engraver3axis.G90.test.cpp src/machine/Engraver3axis.G91.test.cpp)

set(
        SOURCES
        src/MainWindow.cpp
        src/SerialPort.cpp
        src/SerialPort.h
        ${SOURCES_GRBL}
        ${SOURCES_GCODE}
        ${SOURCES_WIDGETS}
        ${SOURCES_MACHINE}
        src/widgets/settings/SettingsTableModel.cpp
        src/widgets/settings/SettingsTableModel.h
        src/utils/SettingCodes.cpp
        src/utils/SettingCodes.h
        src/widgets/delegates/LineEditItemDelegate.cpp
        src/widgets/delegates/LineEditItemDelegate.cpp
        src/widgets/delegates/LineEditItemDelegate.h
        src/utils/ErrorCodes.cpp
        src/utils/ErrorCodes.h
        src/machine/Machine.cpp)

add_executable(grbl
        src/main.cpp
        ${SOURCES}
        resources/resources.qrc
        )

set_target_properties(grbl PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/resources/Info.plist.in
        MACOSX_BUNDLE TRUE
        MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
        RESOURCE "${RESOURCE_FILES}"
        )

target_link_libraries(grbl
        Qt5::Widgets
        Qt5::SerialPort)

set(COVERAGE_EXCLUDES **/*.test.*)

add_executable(
        grbl-test
        ${SOURCES_MACHINE}
        ${SOURCES_GRBL}
        ${SOURCES_GCODE}
        ${SOURCES_GCODE_TEST}
        ${SOURCES_MACHINE}
        ${SOURCES_MACHINE_TESTS}
        resources/resources.qrc
        src/grbl/GRBL.test.cpp
        src/grbl/Message.test.cpp
        src/grbl/parsers/alarm/AlarmParser.test.cpp
        src/grbl/parsers/response_message/ResponseMessageParser.test.cpp
        src/grbl/parsers/setting/SettingParser.test.cpp
        src/grbl/parsers/status_report/accessory_state/AccessoryStateParser.test.cpp
        src/grbl/parsers/status_report/buffer_state/BufferStateParser.test.cpp
        src/grbl/parsers/status_report/feed_rate/FeedRateParser.test.cpp
        src/grbl/parsers/status_report/feed_rate_spindle_speed/FeedRateAndSpindleSpeedParser.test.cpp
        src/grbl/parsers/status_report/input_pin_state/InputPinStateParser.test.cpp
        src/grbl/parsers/status_report/line_number/LineNumberParser.test.cpp
        src/grbl/parsers/status_report/machine_state/MachineStateParser.test.cpp
        src/grbl/parsers/status_report/overridden_values/OverridenValuesParser.test.cpp
        src/grbl/parsers/status_report/position_parser/PositionParser.test.cpp
        src/grbl/parsers/welcome_message/WelcomeMessageParser.test.cpp
        src/utils/SettingCodes.test.cpp
        tests/TestSuite.cpp
        tests/TestSuite.h
        tests/main.cpp
)

file(COPY fixtures/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fixtures/)

include(cmake-modules/CodeCoverage.cmake)
append_coverage_compiler_flags()

target_link_libraries(
        grbl-test
        Qt5::Widgets
        Qt5::SerialPort
        Qt5::Test
)
