#include "ControlMain/controlmain.h"

static ControlMain *controlMain;

int main()
{
    controlMain = new ControlMain();
    controlMain->start();

    while(true){
    }

    delete controlMain;
    usleep(10000);

    return 0;
}
