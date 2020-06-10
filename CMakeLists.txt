cmake_minimum_required(VERSION 3.0.0)
project(placement_manager)
add_compile_options(-std=c++11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(HEADER
    DataControl/datacontrol.h
    MainVisionModule/mainvisionmodule.h
    PlaceVisionModule/placevisionmodule.h
    ControlMain/controlmain.h
    Dynamixel/dynamixel.h
    IRRobot/irrobot.h
    IRRobot/Exception.h
    IRRobot/SerialPort.h
    Conveyor/conveyor.h
    Logger/logger.h
)

set(SOURCE
    main.cpp
    DataControl/datacontrol.cpp
    MainVisionModule/mainvisionmodule.cpp
    PlaceVisionModule/placevisionmodule.cpp
    ControlMain/controlmain.cpp
    Dynamixel/dynamixel.cpp
    IRRobot/irrobot.cpp
    IRRobot/SerialPort.cpp
    Conveyor/conveyor.cpp
    Logger/logger.cpp
)

add_executable(${PROJECT_NAME} ${HEADER} ${SOURCE})
target_link_libraries(${PROJECT_NAME} dxl_sbc_cpp pthread ljacklm)
