#include "conveyor.h"

Conveyor::Conveyor()
{
    version = 0.0;
    errorcode = 0;

    idnum = -1;  //Using first found U12
    demo = 0;  //Normal operations
    stateIO = 0;  //Output states for IO0-IO3

    //AOUpdate specific paramters
    trisD = 0;  //Directions for D0-D15
    trisIO = 0;  //Directions for IO0-IO3
    stateD = 0;  //Output states for D0-D15
    updateDigital = 0;  //Tris and state values are only being read
    resetCounter = 0;  //Not resetting counter
    count = 0;  //Returned current count value
    analogOut0 = 0.8;  //Voltage for AO0
    analogOut1 = 3.2;  //Voltage for AO1

    //AISample specific parameters
    updateIO = 0;  //State values are only being read
    ledOn = 0;  //Turning LED on
    numChannels = 2;  //Reading 2 channels
//    channels[2] = {2, 3};  //Reading AI2 and AI3
    channels[0] = 2;
    channels[1] = 3;
//    gains[2] = {0, 0};  //Gains.  Does not matter in this case since we are
    gains[0] = 0;
    gains[1] = 0;
                             //performing single ended readings.
    disableCal = 0;  //Will apply calibration constants
    overVoltage = 0;  //Returns if overvoltage was detected (>1)
//    voltages[4] = {0};  //Returned voltage readings.  Pass an array of all zeros.
    memset(voltages, 0, sizeof(float)*4);
}

Conveyor::~Conveyor()
{
    stop();
}

void Conveyor::run()
{
    analogOut1 = 2.0;  //Voltage for AO1
    errorcode = AOUpdate(&idnum, demo, trisD, trisIO, &stateD, &stateIO, updateDigital, resetCounter, &count, analogOut0, analogOut1);
}

void Conveyor::stop()
{
    analogOut1 = 0.0;  //Voltage for AO1
    errorcode = AOUpdate(&idnum, demo, trisD, trisIO, &stateD, &stateIO, updateDigital, resetCounter, &count, analogOut0, analogOut1);
}
