# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Project/placement-manager

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Project/placement-manager/build_pi

# Include any dependencies generated for this target.
include CMakeFiles/placement_manager.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/placement_manager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/placement_manager.dir/flags.make

CMakeFiles/placement_manager.dir/main.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/placement_manager.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/main.cpp.o -c /home/pi/Project/placement-manager/main.cpp

CMakeFiles/placement_manager.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/main.cpp > CMakeFiles/placement_manager.dir/main.cpp.i

CMakeFiles/placement_manager.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/main.cpp -o CMakeFiles/placement_manager.dir/main.cpp.s

CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.o: ../DataControl/datacontrol.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.o -c /home/pi/Project/placement-manager/DataControl/datacontrol.cpp

CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/DataControl/datacontrol.cpp > CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.i

CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/DataControl/datacontrol.cpp -o CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.s

CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.o: ../MainVisionModule/mainvisionmodule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.o -c /home/pi/Project/placement-manager/MainVisionModule/mainvisionmodule.cpp

CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/MainVisionModule/mainvisionmodule.cpp > CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.i

CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/MainVisionModule/mainvisionmodule.cpp -o CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.s

CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.o: ../PlaceVisionModule/placevisionmodule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.o -c /home/pi/Project/placement-manager/PlaceVisionModule/placevisionmodule.cpp

CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/PlaceVisionModule/placevisionmodule.cpp > CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.i

CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/PlaceVisionModule/placevisionmodule.cpp -o CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.s

CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.o: ../ControlMain/controlmain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.o -c /home/pi/Project/placement-manager/ControlMain/controlmain.cpp

CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/ControlMain/controlmain.cpp > CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.i

CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/ControlMain/controlmain.cpp -o CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.s

CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.o: ../Dynamixel/dynamixel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.o -c /home/pi/Project/placement-manager/Dynamixel/dynamixel.cpp

CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/Dynamixel/dynamixel.cpp > CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.i

CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/Dynamixel/dynamixel.cpp -o CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.s

CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.o: ../IRRobot/irrobot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.o -c /home/pi/Project/placement-manager/IRRobot/irrobot.cpp

CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/IRRobot/irrobot.cpp > CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.i

CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/IRRobot/irrobot.cpp -o CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.s

CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.o: ../IRRobot/SerialPort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.o -c /home/pi/Project/placement-manager/IRRobot/SerialPort.cpp

CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/IRRobot/SerialPort.cpp > CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.i

CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/IRRobot/SerialPort.cpp -o CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.s

CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.o: ../Conveyor/conveyor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.o -c /home/pi/Project/placement-manager/Conveyor/conveyor.cpp

CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/Conveyor/conveyor.cpp > CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.i

CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/Conveyor/conveyor.cpp -o CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.s

CMakeFiles/placement_manager.dir/Logger/logger.cpp.o: CMakeFiles/placement_manager.dir/flags.make
CMakeFiles/placement_manager.dir/Logger/logger.cpp.o: ../Logger/logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/placement_manager.dir/Logger/logger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/placement_manager.dir/Logger/logger.cpp.o -c /home/pi/Project/placement-manager/Logger/logger.cpp

CMakeFiles/placement_manager.dir/Logger/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/placement_manager.dir/Logger/logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Project/placement-manager/Logger/logger.cpp > CMakeFiles/placement_manager.dir/Logger/logger.cpp.i

CMakeFiles/placement_manager.dir/Logger/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/placement_manager.dir/Logger/logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Project/placement-manager/Logger/logger.cpp -o CMakeFiles/placement_manager.dir/Logger/logger.cpp.s

# Object files for target placement_manager
placement_manager_OBJECTS = \
"CMakeFiles/placement_manager.dir/main.cpp.o" \
"CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.o" \
"CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.o" \
"CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.o" \
"CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.o" \
"CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.o" \
"CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.o" \
"CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.o" \
"CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.o" \
"CMakeFiles/placement_manager.dir/Logger/logger.cpp.o"

# External object files for target placement_manager
placement_manager_EXTERNAL_OBJECTS =

placement_manager: CMakeFiles/placement_manager.dir/main.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/DataControl/datacontrol.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/MainVisionModule/mainvisionmodule.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/PlaceVisionModule/placevisionmodule.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/ControlMain/controlmain.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/Dynamixel/dynamixel.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/IRRobot/irrobot.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/IRRobot/SerialPort.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/Conveyor/conveyor.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/Logger/logger.cpp.o
placement_manager: CMakeFiles/placement_manager.dir/build.make
placement_manager: CMakeFiles/placement_manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Project/placement-manager/build_pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable placement_manager"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/placement_manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/placement_manager.dir/build: placement_manager

.PHONY : CMakeFiles/placement_manager.dir/build

CMakeFiles/placement_manager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/placement_manager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/placement_manager.dir/clean

CMakeFiles/placement_manager.dir/depend:
	cd /home/pi/Project/placement-manager/build_pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Project/placement-manager /home/pi/Project/placement-manager /home/pi/Project/placement-manager/build_pi /home/pi/Project/placement-manager/build_pi /home/pi/Project/placement-manager/build_pi/CMakeFiles/placement_manager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/placement_manager.dir/depend

