QT -= gui
QT += core serialport

CONFIG += c++11 console
CONFIG -= app_bundle

HEADERS += \
    DataControl/datacontrol.h \
    MainVisionModule/mainvisionmodule.h \
    PlaceVisionModule/placevisionmodule.h \
    ControlMain/controlmain.h \
    Dynamixel/dynamixel.h \
    IRRobot/irrobot.h \
    IRRobot/Exception.h \
    IRRobot/SerialPort.h \
    Conveyor/conveyor.h \
    Logger/logger.h \

SOURCES += main.cpp \
    DataControl/datacontrol.cpp \
    MainVisionModule/mainvisionmodule.cpp \
    PlaceVisionModule/placevisionmodule.cpp \
    ControlMain/controlmain.cpp \
    Dynamixel/dynamixel.cpp \
    IRRobot/irrobot.cpp \
    IRRobot/SerialPort.cpp \
    Conveyor/conveyor.cpp \
    Logger/logger.cpp \


LIBS += -L$$PWD/Dynamixel/ -ldxl_x64_cpp

INCLUDEPATH += $$PWD/Dynamixel
DEPENDPATH += $$PWD/Dynamixel

LIBS += -L$$PWD/Conveyor/libljacklm/ -lljacklm

INCLUDEPATH += $$PWD/Conveyor/libljacklm
DEPENDPATH += $$PWD/Conveyor/libljacklm
