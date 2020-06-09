***

### Environment

#### Linux Version : Ubuntu 18.04.3 LTS
#### Compiler Version : gcc-7.5.0, g++-7.5.0
#### CMake Version : 3.10.2

***

### 1. Dynamixel SDK Download & Install
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
U12 driver [ljacklm_2017_03_09.zip](https://labjack.com/support/software/installers/u12/u12-mac-and-linux-ljacklm) download
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

