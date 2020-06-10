***

### Environment

#### Linux Version : Ubuntu 18.04.3 LTS
#### Compiler Version : gcc-7.5.0, g++-7.5.0
#### CMake Version : 3.10.2

***

### 1. Dynamixel SDK Download & Install
[DynamixelSDK](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/download/)
[DynamixelSDK Protocol 2.0](https://emanual.robotis.com/docs/en/dxl/protocol2/)
~~~
$ git clone https://github.com/ROBOTIS-GIT/DynamixelSDK.git
$ cd DynamixelSDK/c++/build/linux64
$ make
$ sudo make install
~~~

### 2. LabJack Library Download & Install
#### 1) required library install
~~~
$ sudo apt-get install build-essential
$ sudo apt-get install libusb-1.0-0-dev
~~~
#### 2) exodriver download and install
~~~
$ git clone https://github.com/labjack/exodriver.git
$ cd exodriver
$ chmod +x install.sh
$ sudo ./install.sh
$ cd liblabjackusb
$ make
$ sudo make install
~~~
#### 3) U12 linux driver download & install
U12 driver [ljacklm_2017_03_09.zip](https://labjack.com/sites/default/files/ljacklm_2017_03_09.zip) download
~~~
$ unzip ljacklm_2017_03_09.zip
$ cd ljacklm/libljacklm
$ make
$ sudo make install
~~~

### 3. Placement Manager Project build & run
~~~
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ./placement_manager
~~~

### 4. Configuration Parameters
~~~
You can check and change the settings by opening the conf.json.

TCP_ADDRESS : IP ADDRESS of the computer to run the project.

MAIN_VISION_PORT : Port number to be connected to vision module PC.

PLACE_VISION_PORT : Port number to be connected to placement vision module PC.

DXL_Origin_Axis_1 : The initial position of the Motor 1.

DXL_Turn_Axis_1 : The position of the Motor 1 when turning the flipper.

DXL_Up_Axis_2 : The position of the Motor 2 when upping the flipper.

DXL_Down_Axis_2 : The positon of the Motor 2 when downing the flipper.

DXL_Block_Axis_1 : The position of the Motor 1 when blocking the object.

DXL_Block_Axis_2 : The position of the Motor 2 when blocking the object.

IRR_Release_Pos : The position of the gripper when opening the gripper.

IRR_Grip_Pos : The position of the gripper when closing the gripper.

IRR_Block_Pos : The position of the gripper when blocking the object.
~~~