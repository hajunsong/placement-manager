#include <QCoreApplication>

#include "ControlMain/controlmain.h"
#include "KeyInput/keyinput.h"

static KeyInput *keyInput;
static ControlMain *controlMain;
static QCoreApplication *app;

void keyInputSlot(char key){
    if (key == 'q' || key == 27 || key == 'c'){
        printf("Pressed 'q' or 'ESC'\n");
        app->exit();
    }
    else if(key == '1'){
        controlMain->run_turn();
    }
    else if(key == '2'){
        controlMain->run_block();
    }
    else if(key == '3'){
        controlMain->run_cancel();
    }
    else if(key == '4'){
        controlMain->run_grip();
    }
    else if(key == '5'){
        controlMain->run_grip_release();
    }
    else if(key == '6'){
        controlMain->run_mover();
    }
    else if(key == '7'){
        controlMain->stop_mover();
    }
}

int main(int argc, char *argv[])
{
    app = new QCoreApplication(argc, argv);

    keyInput = new KeyInput();
    QObject::connect(keyInput, &KeyInput::KeyPressed, keyInputSlot);
    keyInput->start();

    controlMain = new ControlMain();
    controlMain->start();

    app->exec();

    delete controlMain;
    usleep(10000);

    return 0;
}
