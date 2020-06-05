#include "ControlMain/controlmain.h"

int main() {
    ControlMain *controlMain = new ControlMain();
    controlMain->start();

    while(true){
        usleep(1000);
    }

    usleep(10000);
    delete controlMain;

    return 0;
}
