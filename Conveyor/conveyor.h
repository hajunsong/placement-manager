#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libljacklm/ljacklm.h"
#include <iostream>
#include <memory.h>
using namespace std;

class Conveyor{
public:
    Conveyor();
    ~Conveyor();
    void run();
    void stop();

private:
    float version = 0.0;
    long errorcode = 0;

    long idnum = -1;  //Using first found U12
    long demo = 0;  //Normal operations
    long stateIO = 0;  //Output states for IO0-IO3

    //AOUpdate specific paramters
    long trisD = 0;  //Directions for D0-D15
    long trisIO = 0;  //Directions for IO0-IO3
    long stateD = 0;  //Output states for D0-D15
    long updateDigital = 0;  //Tris and state values are only being read
    long resetCounter = 0;  //Not resetting counter
    unsigned long count = 0;  //Returned current count value
    float analogOut0 = 0.8;  //Voltage for AO0
    float analogOut1 = 3.2;  //Voltage for AO1

    //AISample specific parameters
    long updateIO = 0;  //State values are only being read
    long ledOn = 0;  //Turning LED on
    long numChannels = 2;  //Reading 2 channels
    long channels[2] = {2, 3};  //Reading AI2 and AI3
    long gains[2] = {0, 0};  //Gains.  Does not matter in this case since we are
                             //performing single ended readings.
    long disableCal = 0;  //Will apply calibration constants
    long overVoltage = 0;  //Returns if overvoltage was detected (>1)
    float voltages[4] = {0};  //Returned voltage readings.  Pass an array of all zeros.
};

#endif // CONVEYOR_H
